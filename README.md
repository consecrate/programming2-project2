# Smart E-Commerce System

Console-based C++17 OOP project for a smart online shopping platform with customer shopping flows, admin product management, file persistence, statistics, and a recommendation engine.

## Build and Run

```sh
make
make run
```

Useful commands:

```sh
make check
make clean
```

The executable is created as `project2` in the project root.

## Demo Accounts

Customer:

```text
Email: josh@email.com
Password: 1234
```

Admin:

```text
Email: admin@email.com
Password: admin123
```

## Main Features

- Customers can register, log in, browse products, view product details, filter by category, manage a cart, checkout, view order history, and receive Top N recommendations.
- Admins can log in, view products, add/edit/delete products, and view most viewed products, best-selling products, and active users.
- Data is loaded on startup and saved when choosing `Save and exit`.
- Product views, purchases, orders, and interactions persist in plain text files.

## Data Files

The project stores data in the `data/` folder:

- `products.txt`: `id|name|category|price|stock|viewCount|purchaseCount`
- `users.txt`: `userId|name|email|password|role`
- `orders.txt`: `orderId|customerId|dateTime|totalPrice|productId,productName,price,quantity;...`
- `interactions.txt`: `customerId|productId|type|count`

## Recommendation Formula

Recommendations are sorted by:

```text
score = view_count * 0.2 + purchase_count * 0.8 + category_bonus
```

The category bonus is `1.5` for categories the customer has purchased before, `0.8` for categories the customer has viewed before, and `0` otherwise. Already-purchased products are excluded.

## Suggested Customer Demo

1. Log in as `josh@email.com` with password `1234`.
2. Browse all products.
3. Search for a product by ID to show detail view tracking.
4. Add a product to the cart and view the cart total.
5. Try adding or updating beyond stock to show validation.
6. Checkout and show the new order in order history.
7. View Top N recommendations.
8. Choose logout, then `Save and exit` to persist data.
