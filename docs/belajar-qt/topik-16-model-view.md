# Topik 16 — Model/View Architecture
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 2 Topik 3)
Project: [modelview_basic/](../../fase-2-intermediate/16-17-model-view-event-handling/)

## Ringkasan konsep
Model/View memisahkan **data** dari **tampilan**. Model nyimpen data dan emit signal saat berubah; View tinggal subscribe ke model dan auto-update. Satu model bisa di-attach ke banyak view (`QListView` + `QComboBox`) — semua sync otomatis tanpa boilerplate. Ini analog dengan state management React: model = state store, view = component yang subscribe.

## Analogi JavaScript/React
| React/Redux | Qt Model/View |
|---|---|
| State store (Redux/Zustand) | `QStringListModel`, `QStandardItemModel`, `QSqlTableModel` |
| Component subscribe via `useSelector` | `view->setModel(model)` |
| `dispatch(action)` → state change → re-render | `model->setData(...)` → emit dataChanged → view update |
| Custom cell renderer | `QStyledItemDelegate` |

## Kode inti
```cpp
// Setup
model = new QStringListModel(this);
model->setStringList({"Jakarta", "Surabaya", "Medan"});

listView->setModel(model);                     // satu view
comboBox->setModel(model);                     // view kedua, auto-sync

// Tambah item
int row = model->rowCount();
model->insertRow(row);
model->setData(model->index(row), "Bandung");

// Hapus — selalu guard dulu
QModelIndex idx = listView->currentIndex();
if (!idx.isValid()) return;                    // guard: tidak ada selection
model->removeRow(idx.row());

// Untuk combobox
int idx2 = comboBox->currentIndex();
if (idx2 < 0) return;                          // guard: model kosong
model->removeRow(idx2);
```

## Aturan penting
- **Kapan pakai Model/View:** data list/table/tree yang bisa berubah, atau perlu tampil di beberapa view sync.
- **Kapan TIDAK pakai:** label statis, data fix yang gak berubah — overkill.
- **Common mistake:** akses `model->data(idx)` tanpa cek `idx.isValid()` → undefined behavior.
- **Common mistake:** lupa guard `currentIndex() < 0` di QComboBox → kalau model kosong, return -1, hapus row -1 = crash.

## Catatan tambahan
- **`QModelIndex` vs `int`:** QModelIndex bawa row + column + parent (support tree/table); `int` cukup untuk list flat.
- Untuk data custom (bukan string), subclass `QAbstractListModel` atau `QAbstractTableModel` dan override `rowCount()`, `data()`, `setData()`, `flags()`.
- `QStandardItemModel` untuk data hierarchical dengan icon/text per item, lebih fleksibel daripada `QStringListModel`.
- Delegate (`QStyledItemDelegate`) untuk custom rendering per cell — analog dengan custom cell renderer di React Table.
