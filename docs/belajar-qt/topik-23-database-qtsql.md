# Topik 23 — Database dengan QtSql
Diarsipkan: 2026-05-29 (dari CATATAN_CPP.md — Fase 4 Topik 2)
Project: [database_basic/](../../database_basic/)

## Ringkasan konsep
`QtSql` module menyediakan abstraction database (SQLite, MySQL, PostgreSQL) dengan API yang sama. SQLite paling sering dipakai untuk app desktop — gak butuh server, datanya 1 file `.db`. Pakai `QSqlTableModel` kalau mau langsung attach DB table ke view (auto-sync); pakai `QSqlQuery` untuk SQL custom. **Wajib pakai prepared statement** (`:placeholder` + `bindValue`) — cegah SQL injection.

## Analogi JavaScript/React
| Node.js | Qt |
|---|---|
| `sqlite3` package | `QSqlDatabase::addDatabase("QSQLITE")` |
| ORM (Sequelize, Prisma) | `QSqlTableModel` (model + table) |
| `db.prepare(sql).run(...)` | `QSqlQuery::prepare()` + `bindValue()` |
| `ON CONFLICT` SQL | Sama persis — SQLite syntax |
| File `.sqlite` | File `.db` |

## Kode inti
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
target_link_libraries(app PRIVATE Qt6::Widgets Qt6::Sql)
```

```cpp
// Setup koneksi
db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("kapal.db");                // file di working dir app
if (!db.open()) { qWarning() << db.lastError(); return; }

// Buat tabel — IF NOT EXISTS supaya idempotent
QSqlQuery query;
query.exec("CREATE TABLE IF NOT EXISTS kapal ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "nama TEXT NOT NULL)");

// Setup model untuk view
model = new QSqlTableModel(this, db);
model->setTable("kapal");
model->setEditStrategy(QSqlTableModel::OnManualSubmit);
model->select();
listView->setModel(model);
listView->setModelColumn(1);                   // 0=id, 1=nama

// INSERT — prepared statement (anti SQL injection)
QSqlQuery q;
q.prepare("INSERT INTO kapal (nama) VALUES (:nama)");
q.bindValue(":nama", input->text());
q.exec();
model->select();                               // refresh view

// DELETE via model
QModelIndex idx = listView->currentIndex();
if (!idx.isValid()) return;
model->removeRow(idx.row());
model->submitAll();                            // WAJIB untuk OnManualSubmit
model->select();
```

## Aturan penting
- **Kapan pakai SQLite:** app desktop single-user, embedded, offline-first.
- **Kapan TIDAK pakai SQLite:** server multi-user concurrent write → pakai PostgreSQL/MySQL.
- **Kapan pakai `QSqlTableModel`:** display tabular data dengan minimal effort.
- **Kapan pakai `QSqlQuery`:** SQL custom (JOIN, aggregate, subquery, prosedur).
- **Common mistake:** lupa `IF NOT EXISTS` di CREATE TABLE → crash di run kedua karena table udah ada.
- **Common mistake:** lupa `model->submitAll()` di `OnManualSubmit` → perubahan ditahan di memory, gak ke-write.
- **Common mistake:** concat string SQL (`"WHERE nama = '" + input + "'"`) → SQL injection. **Selalu** pakai `:placeholder`.

## Catatan tambahan
- File `.db` posisinya di **working directory app saat dijalankan** — biasanya `build/` folder kalau jalan dari Qt Creator.
- `EditStrategy`:
  - `OnFieldChange` — setiap edit langsung commit ke DB
  - `OnRowChange` — commit saat pindah row
  - `OnManualSubmit` — wajib `submitAll()` (paling kontrol, support undo)
- Backup database = copy file `.db` (gak perlu dump SQL).
- Untuk SQLite, pertimbangkan `PRAGMA journal_mode=WAL` untuk konkurensi lebih baik (read + write bareng).
