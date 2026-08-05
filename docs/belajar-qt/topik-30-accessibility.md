# Topik 30 — Qt Accessibility
Tanggal: 2026-06-03

## Ringkasan konsep
Qt accessibility framework bridge widget properties ke assistive technology OS (AT-SPI di Linux, NSAccessibility di macOS, UIA/MSAA di Windows) — gak perlu code per-platform. Real a11y = **multi-pillar**: semantic naming (`accessibleName`/`accessibleDescription`), keyboard navigation (Tab order + accelerator `&`), multi-modal signaling (text + icon + color, bukan color-only), focus indicator visible, dan contrast ratio cukup (WCAG AA 4.5:1). Setiap jenis widget punya mode failure berbeda — slider butuh live value announcement, indicator butuh multi-modal, icon-only button butuh accessibleName, dropdown cukup context name. Accessibility kalau dari awal = 5-10% effort tambahan; retrofit = jauh lebih mahal plus risiko regulasi (IMO MSC.232 maritime, EU EN 301 549, WCAG 2.1 AA) dan reputasi.

## Analogi JavaScript/React
| Web / ARIA | Qt |
|---|---|
| `aria-label` | `setAccessibleName(...)` |
| `aria-describedby` | `setAccessibleDescription(...)` |
| `<label for="x">` | `QLabel("&Text") + setBuddy(target)` |
| `accesskey="u"` | `&` di label/button text |
| `tabindex` | `setTabOrder(prev, next)` (declarative pair) |
| `:focus { outline: ... }` | Qt default outline (jangan disable kecuali ganti yang lebih baik) |
| WCAG 1.4.1 (no color-only) | Multi-modal: text + icon + color |
| `aria-live="polite"` | Update `accessibleDescription` saat state berubah |

## Kode inti

### Form login dengan accessibility lengkap
```cpp
// Label dengan accelerator + buddy → Alt+U focus ke field
auto* lblUser = new QLabel("&Username:");
lblUser->setBuddy(usernameField);

usernameField->setAccessibleName("Username atau Email");
usernameField->setAccessibleDescription("Masukkan username atau alamat email");

// Tab order eksplisit (jangan trust default)
setTabOrder(usernameField, passwordField);
setTabOrder(passwordField, rememberCheckbox);
setTabOrder(rememberCheckbox, loginBtn);

// Default button (Enter trigger)
loginBtn->setDefault(true);

// Error signaling multi-modal: icon + text + color + behavior
statusLabel->setText("⚠ Username tidak boleh kosong");
statusLabel->setStyleSheet("color: #c0392b; font-weight: bold;");
usernameField->setFocus();   // bantu keyboard user
```

### Live update untuk widget stateful (slider, progressbar)
```cpp
connect(thrust, &QSlider::valueChanged, this, [this](int v) {
    thrust->setAccessibleDescription(QString("Thrust %1 persen").arg(v));
});
```

### Multi-modal status indicator (anti color-only)
```cpp
// SALAH — color-only signaling
statusLight->setStyleSheet("background: green;");

// BENAR — text + icon + color + a11y
statusLight->setText("✓ OK");
statusLight->setStyleSheet("background: green; color: white; padding: 8px;");
statusLight->setAccessibleName("Status Engine");
statusLight->setAccessibleDescription("Engine OK, beroperasi normal");
```

## Aturan penting
- **Kapan wajib invest a11y:** app publik, B2B dengan diverse user, compliance (maritime IMO, EU EN 301 549, US Section 508), tool internal dengan disabled team member.
- **Kapan keyboard nav saja cukup:** dev tool internal — tetap wajib Tab order + shortcut.
- **Common mistake:** `setAccessibleName` redundant dengan visible text → screen reader baca double ("Tombol Masuk, Masuk").
- **Common mistake:** Color-only signaling untuk status → 8% pria color-blind silently miss warning.
- **Common mistake:** Icon-only button tanpa `accessibleName` → screen reader baca "Button" generic.
- **Common mistake:** Custom widget override paint tanpa redraw focus indicator → keyboard user gak tau widget mana yang aktif.
- **Common mistake:** Trust default Tab order → layout kompleks loncat-loncat random.
- **`&` accelerator marker behavior:** auto-aktif di widget interactive dengan text (QPushButton, QCheckBox, QAction). Butuh `setBuddy()` di QLabel kalau target widget non-text (QLineEdit, QComboBox).

## Hasil eksperimen
- **Eksp 1 (Tab order tanpa setTabOrder):** Default Qt tab order **bukan pure construct order** — heuristic juga consider posisi widget di layout. Hasilnya unpredictable di layout kompleks (nested QSplitter, dst). Selalu set eksplisit dengan `setTabOrder` chain untuk app production.
- **Eksp 2 (QLabel tanpa setBuddy):** Tanpa buddy, `&` di text QLabel ditampilkan **literal** (string jadi `"&Username:"`), dan Alt+U gak ada efek. Logic Qt: label tanpa buddy = display-only, accelerator gak punya target sehingga dimatikan. Buddy diperlukan untuk QLineEdit/QComboBox/QSpinBox; tidak diperlukan untuk widget interactive bertext sendiri (QPushButton, QCheckBox).
- **Eksp 3 (accessibleName berbeda dari visible text):** Screen reader baca `accessibleName`, sighted user baca visible text. Kalau beda secara material → dual-modal user (low-vision + screen reader bareng) bingung. Best practice: `accessibleName` cuma elaborate visible text, bukan tambah info baru. Pakai `accessibleName` cuma kalau widget gak punya visible text (icon-only) atau visible text ambigu.

## Jawaban cek paham

### 1. Audit accessibility panel kontrol pesawat (4 komponen)

**(1) Slider thrust 0-100%**
- **Issue kritis:** Value gak announced saat user nge-arrow. Pilot blind gak tau thrust sekarang berapa.
- **Fix:** Set `accessibleName("Thrust Engine")` + dynamic `accessibleDescription` di `valueChanged` signal yang update "Thrust X persen" tiap kali nilai berubah. Keyboard navigation udah otomatis (Arrow keys + PageUp/PageDown).

**(2) Indicator lampu hijau/merah**
- **Issue kritis:** Color-only signaling. 8% pria color-blind tidak bisa bedakan; screen reader user tidak dapat info sama sekali.
- **Fix:** Multi-modal. Tambah text ("✓ OK" / "⚠ WARNING"), icon symbol, plus warna sebagai reinforcement. Set `accessibleName("Status Engine")` + `accessibleDescription` dengan state aktual.

**(3) Icon-only emergency button**
- **Issue kritis:** Tanpa text + tanpa accessibleName, screen reader cuma baca "Button" generic. Pilot blind gak tau ini tombol emergency.
- **Fix:** WAJIB `accessibleName("EMERGENCY: Eject")` + `accessibleDescription` dengan instruksi. Pertimbangkan juga double-click/hold pattern untuk cegah accidental trigger di safety-critical context.

**(4) Dropdown mode**
- **Issue minor:** Default `QComboBox` udah accessible (screen reader announce selection saat berubah). Yang kurang cuma context.
- **Fix:** `setAccessibleName("Mode Pesawat")` + `accessibleDescription` daftarin opsi.

**Pelajaran:** "Tambah accessibleName" bukan silver bullet. Setiap widget kategori punya mode failure spesifik. Slider butuh live announcement, color indicator butuh multi-modal, icon-only button WAJIB text equivalent.

### 2. Trade-off accessibility di MVP

**Angle A — Engineering effort:** Klaim PM "30% effort" mitos. Realnya 5-10% kalau dari awal. 80% accessibility (semantic naming, Tab order, accelerator) = boilerplate API call yang negligible. 20% (multi-modal design, keyboard-first navigation) = murah kalau di-arsitek dari awal, mahal kalau retrofit (visual designer rework + brand inconsistency).

**Angle B — Regulasi & bisnis:**
- ECDIS = maritime (IMO MSC.232(82), IEC 62288, SOLAS Ch V) — multi-channel feedback wajib di emergency context.
- EU = EN 301 549 wajib untuk software entity publik.
- US = Section 508 untuk gov procurement.
- WCAG 2.1 AA = de facto B2B contract requirement.
- Reputational risk: lawsuit history (target.com $6M, Domino's Pizza), social media blow-up bisa permanently damage brand.

**Angle C — Subset minimum yang TETAP di MVP:**
1. Semantic naming (`accessibleName`/`Description`) untuk semua interactive widget (1-2 hari).
2. Keyboard navigation + Tab order eksplisit (0 effort, cuma discipline).
3. Multi-modal signaling untuk status critical (0 code effort, design choice).
4. Focus indicator visible (0 effort, jangan disable default).
5. Contrast ratio WCAG AA 4.5:1 (design check pakai tool).

**Defer ke patch (OK):**
- Custom `QAccessibleWidget` subclass untuk widget kompleks.
- Screen reader edge case widget khusus.
- RTL layout direction.
- Live region async update.
- Motion reduction preference.

**Posisi ke PM:** "Setuju defer custom widget a11y. Tapi 1-5 ini engineering quality baseline — sama level dengan error handling. Effort include di MVP cuma 1 minggu max. Skip a11y bukan save time, tapi shifting cost ke quarter berikutnya dengan bunga regulasi + reputational risk."

## Catatan tambahan
- **Accessible name computation priority** di Qt: explicit `accessibleName` → visible text widget → tooltip → class name default (generic, jelek).
- **`QShortcut`** untuk shortcut global yang gak terkait widget (Ctrl+S save). Beda dengan `&` accelerator yang konteks-spesifik.
- **`setDefault(true)`** di QPushButton bikin Enter dari mana saja di form trigger button itu. Berguna untuk dialog (OK button) atau form (Login).
- **`setFocus()` programmatic** setelah error helpful untuk keyboard user — gak perlu Tab manual ke field yang salah.
- **WCAG 1.4.1 Use of Color** — informasi gak boleh disampaikan dengan warna saja. Selalu kombinasi text + icon + color.
- **Testing tools:**
  - Linux: Orca (`sudo apt install orca`, toggle Ctrl+Alt+Super+S).
  - macOS: VoiceOver (Cmd+F5).
  - Windows: Narrator (Win+Ctrl+Enter), NVDA (gratis), JAWS (paid).
- **`QAccessible`** namespace untuk custom widget — subclass `QAccessibleWidget` kalau bikin widget custom yang gak inherit perilaku standar. Topic advanced di luar scope dasar.
- **High contrast mode:** Qt auto-respect OS setting (Windows High Contrast, macOS Increase Contrast). Custom QSS kalau aktif bisa override — hati-hati.
- **Motion preference:** macOS dan Windows punya "Reduce Motion" setting. Untuk animasi non-essential, cek `QGuiApplication::styleHints()->showShortcutsInContextMenus()` atau platform API.
