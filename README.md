[README (1).md](https://github.com/user-attachments/files/31053144/README.1.md)
# Simple Warehouse Management System

A console-based warehouse management system written in C++, built as an object-oriented programming (OOP) practice project. It tracks products, shelf locations, stock levels, and incoming/outgoing movements — all through a simple text menu.

## Features

- **Add a new product** — assigns a unique product number automatically, starting from 1.
- **Stock in (goods receipt)** — add incoming stock to an existing product.
- **Stock out (shipment)** — remove stock, with a check to prevent shipping more than what's available.
- **Update shelf location** — change where a product is stored in the warehouse (e.g. A1, B3).
- **Look up a product** — check the current stock and shelf location of a specific product.
- **List all products** — view every product currently in the warehouse.
- **Low stock alert** — see which products have fewer than 5 units left.
- **Movement history** — view a log of every stock-in and stock-out transaction.

## How to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/ataaygun/warehouse.git
   cd warehouse
   ```

2. Compile the source code:
   ```bash
   g++ -std=c++17 -o warehouse warehouse.cpp
   ```

3. Run the program:
   ```bash
   ./warehouse
   ```

4. Use the on-screen menu to perform warehouse operations.

## Example Usage

```
===== DEPO (WAREHOUSE) YONETIM SISTEMI =====
1. Yeni Urun Ekle
2. Depoya Giris Yap (Mal Kabul)
3. Depodan Cikis Yap (Sevkiyat)
4. Raf Konumu Guncelle
5. Urun Sorgula
6. Tum Urunleri Listele
7. Dusuk Stok Uyarisi (5 adet altinda)
8. Giris/Cikis Hareket Gecmisi
0. Cikis
Seciminiz: 1

Urun adi: Laptop
Raf konumu (ornek: A1, B3): A1
Baslangic stok adedi: 20
Urun basariyla eklendi! Urun No: 1
```

## Project Structure

- **`Urun`** class — represents a single product (product number, name, shelf location, stock count). Handles its own stock-in and stock-out logic.
- **`Depo`** class — manages the collection of products and keeps a log of every stock movement.
- **`Hareket`** struct — a lightweight data structure used to record each stock-in/stock-out event (product, type, quantity).

Before any operation (stock in, stock out, location update, lookup), the program checks whether the product exists. If it doesn't, the user gets a clear error message instead of a crash. Stock-out operations also check available quantity before removing stock, so a product can never go negative.

## Possible Improvements

- Save and load warehouse data from a file so it persists between runs.
- Support multiple warehouses or zones.
- Add supplier and order tracking.
- Export movement history to a CSV report.

## Note

This project was built for learning purposes and is not a real warehouse management system. All data is stored in memory only — everything is lost once the program closes.
