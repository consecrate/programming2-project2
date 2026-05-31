PRD: Project 2 — Smart E-Commerce System with Recommendation Engine

1. Product Overview

This project is a C++ Object-Oriented Programming system that simulates a smart online shopping platform. Customers can browse products, add products to a shopping cart, purchase products, view order history, and receive product recommendations. Administrators can manage products and view system statistics such as most viewed products, best-selling products, and active users.

The system must also include a recommendation engine that suggests the Top N products based on user behavior. The recommendation score follows this required formula:

score = view_count * 0.2 + purchase_count * 0.8 + category_bonus

All important data should be stored in files, such as TXT, CSV-style TXT, or JSON. For this project, plain TXT/CSV-style storage is recommended because it is easier to implement. 

2. Goals

The goal is to build a complete, clean, and demonstrable OOP project that satisfies all assignment requirements and shows strong software design.

The project should demonstrate:

* Encapsulation through private data members and public methods.
* Inheritance through a base User class and derived Customer and Admin classes.
* Polymorphism through virtual menu or role behavior.
* Composition through objects such as Customer owning a Cart, Cart containing CartItems, and Order containing OrderItems.
* File persistence through loading and saving products, users, orders, and interactions.
* Recommendation logic based on user views, purchases, and category preferences.
* Clear separation of responsibilities across multiple .h and .cpp files.

3. Non-Goals

The project does not need:

* A graphical user interface.
* Real payment processing.
* Real login security or password encryption.
* A real database.
* Advanced machine learning.
* Networking or online functionality.

The system can be a console-based menu application.

4. User Roles

4.1 Customer

A customer should be able to:

* Register or log in.
* Browse all products.
* Search products by ID or name.
* Filter products by category.
* View product details.
* Add products to cart.
* Remove products from cart.
* Update product quantity in cart.
* View cart.
* Checkout from cart.
* View order history.
* Receive Top N product recommendations.

4.2 Administrator

An administrator should be able to:

* Log in.
* Add new products.
* Edit existing products.
* Delete products.
* View all products.
* View most viewed products.
* View best-selling products.
* View active users.
* Save product changes to file.

5. Core Functional Requirements

5.1 Product Browsing

The system should display products with useful information:

* Product ID
* Product name
* Category
* Price
* Stock quantity

When a customer views a specific product in detail, the system should increment that product’s viewCount and record the interaction in the interaction history.

5.2 Shopping Cart

The cart should support:

* Adding a product by product ID and quantity.
* Removing a product by product ID.
* Updating quantity.
* Viewing all cart items.
* Calculating total price.
* Clearing cart after successful checkout.

The system must validate stock before allowing checkout.

5.3 Order Processing

Checkout should:

* Verify the cart is not empty.
* Verify product stock is sufficient.
* Calculate total price.
* Create an order.
* Store order history.
* Reduce product stock.
* Increase product purchase count.
* Record purchase interactions.
* Clear the cart after successful checkout.

5.4 Admin Product Management

The admin should be able to:

* Add product.
* Edit product name.
* Edit category.
* Edit price.
* Edit stock quantity.
* Delete product.
* View all products.

Product IDs should be unique.

5.5 Statistics

The system should calculate:

* Most viewed products, sorted by viewCount descending.
* Best-selling products, sorted by purchaseCount descending.
* Active users, sorted by total number of views and purchases.

A practical definition of active user:

activity_score = total_views_by_user + total_purchases_by_user

5.6 Recommendation Engine

The recommendation engine should output Top N recommended products.

Input:

* Product list.
* Current customer’s view history.
* Current customer’s purchase history.
* Product categories viewed or purchased by the customer.

Output:

* Top N products sorted by recommendation score.

Required scoring formula:

score = view_count * 0.2 + purchase_count * 0.8 + category_bonus

Recommended interpretation of category_bonus:

category_bonus = 1.5 if customer has purchased from this category before
category_bonus = 0.8 if customer has viewed this category before
category_bonus = 0 otherwise

If the customer has both viewed and purchased from the category, use the higher bonus of 1.5.

The recommendation engine should usually avoid recommending products the customer has already purchased, unless the product is reusable or repurchasable. For this project, the simpler choice is to exclude already-purchased products.

6. Technical Architecture

The project should use a layered design:

main.cpp
  -> Application/Menu Layer
      -> Customer / Admin
          -> ProductManager
          -> Cart
          -> OrderManager
          -> RecommendationEngine
          -> StatisticsManager
          -> FileManager
              -> data/*.txt

The main.cpp file should stay small. It should only load data, show the first menu, route users to customer/admin flows, and save data before exit.

Most real logic should live inside classes.

7. Full File List

7.1 Root Files

Project2/
  README.md
  Makefile or compile_instructions.txt
  report.docx or report.pdf

7.2 Source Folder

src/
  main.cpp
  Product.cpp
  ProductManager.cpp
  User.cpp
  Customer.cpp
  Admin.cpp
  CartItem.cpp
  Cart.cpp
  OrderItem.cpp
  Order.cpp
  OrderManager.cpp
  Interaction.cpp
  RecommendationEngine.cpp
  StatisticsManager.cpp
  FileManager.cpp
  Utils.cpp

7.3 Header Folder

include/
  Product.h
  ProductManager.h
  User.h
  Customer.h
  Admin.h
  CartItem.h
  Cart.h
  OrderItem.h
  Order.h
  OrderManager.h
  Interaction.h
  RecommendationEngine.h
  StatisticsManager.h
  FileManager.h
  Utils.h

7.4 Data Folder

data/
  products.txt
  users.txt
  orders.txt
  interactions.txt

7.5 Optional Testing Folder

tests/
  test_cart.cpp
  test_recommendations.cpp
  test_file_loading.cpp

The testing folder is optional. If time is limited, create a manual testing section in the report instead.

8. File Responsibilities

8.1 main.cpp

Purpose:

* Program entry point.
* Load data from files.
* Show login/register/start menu.
* Route to customer or admin menu.
* Save data before program exits.

Should not contain:

* Cart logic.
* Recommendation logic.
* Product CRUD details.
* File parsing details.

Expected functions:

int main();
void showStartMenu();

Owner: Shared, but only one person should edit this file at a time.

8.2 Product.h / Product.cpp

Purpose:

Represents one product in the store.

Fields:

int id;
string name;
string category;
double price;
int stock;
int viewCount;
int purchaseCount;

Important methods:

Product();
Product(int id, string name, string category, double price, int stock);
int getId() const;
string getName() const;
string getCategory() const;
double getPrice() const;
int getStock() const;
int getViewCount() const;
int getPurchaseCount() const;
void setName(string name);
void setCategory(string category);
void setPrice(double price);
void setStock(int stock);
void incrementViewCount();
void incrementPurchaseCount(int quantity);
void reduceStock(int quantity);
void displaySummary() const;
void displayDetails() const;

Owner: Shared during skeleton stage, then HX should own if they own product management.

8.3 ProductManager.h / ProductManager.cpp

Purpose:

Stores and manages the product list.

Fields:

vector<Product> products;

Important methods:

vector<Product>& getProducts();
const vector<Product>& getProducts() const;
Product* findProductById(int id);
bool productExists(int id) const;
void addProduct(const Product& product);
bool editProduct(int id);
bool deleteProduct(int id);
void displayAllProducts() const;
void displayProductsByCategory(string category) const;

Owner: HX.

8.4 User.h / User.cpp

Purpose:

Base class for all users.

Fields:

int userId;
string name;
string email;
string password;
string role;

Important methods:

User();
User(int userId, string name, string email, string password, string role);
int getUserId() const;
string getName() const;
string getEmail() const;
string getRole() const;
bool checkPassword(string inputPassword) const;
virtual void showMenu() = 0;
virtual ~User();

Owner: Shared during skeleton stage, then Josh or HX depending on who starts user login.

8.5 Customer.h / Customer.cpp

Purpose:

Represents customer behavior.

Fields:

Cart cart;
vector<int> viewedProductIds;
vector<int> purchasedProductIds;

Important methods:

Customer();
Customer(int userId, string name, string email, string password);
void showMenu(ProductManager& productManager,
              OrderManager& orderManager,
              RecommendationEngine& recommendationEngine,
              FileManager& fileManager);
void browseProducts(ProductManager& productManager);
void viewProductDetails(ProductManager& productManager, int productId);
void addToCart(ProductManager& productManager, int productId, int quantity);
void removeFromCart(int productId);
void updateCartQuantity(int productId, int quantity);
void checkout(ProductManager& productManager, OrderManager& orderManager);
void viewOrderHistory(OrderManager& orderManager) const;
void viewRecommendations(ProductManager& productManager, RecommendationEngine& recommendationEngine);
vector<int> getViewedProductIds() const;
vector<int> getPurchasedProductIds() const;
void addViewedProductId(int productId);
void addPurchasedProductId(int productId);

Owner: Josh.

8.6 Admin.h / Admin.cpp

Purpose:

Represents administrator behavior.

Important methods:

Admin();
Admin(int userId, string name, string email, string password);
void showMenu(ProductManager& productManager,
              StatisticsManager& statisticsManager,
              OrderManager& orderManager);
void addProduct(ProductManager& productManager);
void editProduct(ProductManager& productManager);
void deleteProduct(ProductManager& productManager);
void viewStatistics(StatisticsManager& statisticsManager,
                    ProductManager& productManager,
                    OrderManager& orderManager);

Owner: HX.

8.7 CartItem.h / CartItem.cpp

Purpose:

Represents one product and quantity inside a cart.

Fields:

int productId;
int quantity;

Important methods:

CartItem();
CartItem(int productId, int quantity);
int getProductId() const;
int getQuantity() const;
void setQuantity(int quantity);

Owner: Josh.

8.8 Cart.h / Cart.cpp

Purpose:

Stores and manages customer cart items.

Fields:

vector<CartItem> items;

Important methods:

void addItem(int productId, int quantity);
bool removeItem(int productId);
bool updateQuantity(int productId, int quantity);
bool isEmpty() const;
double calculateTotal(const ProductManager& productManager) const;
void displayCart(const ProductManager& productManager) const;
void clear();
vector<CartItem> getItems() const;

Owner: Josh.

8.9 OrderItem.h / OrderItem.cpp

Purpose:

Represents one purchased item inside an order.

Fields:

int productId;
string productName;
double priceAtPurchase;
int quantity;

Important methods:

OrderItem();
OrderItem(int productId, string productName, double priceAtPurchase, int quantity);
int getProductId() const;
string getProductName() const;
double getPriceAtPurchase() const;
int getQuantity() const;
double getSubtotal() const;

Owner: Josh.

8.10 Order.h / Order.cpp

Purpose:

Represents a completed order.

Fields:

int orderId;
int customerId;
vector<OrderItem> items;
double totalPrice;
string dateTime;

Important methods:

Order();
Order(int orderId, int customerId, vector<OrderItem> items, double totalPrice, string dateTime);
int getOrderId() const;
int getCustomerId() const;
double getTotalPrice() const;
string getDateTime() const;
vector<OrderItem> getItems() const;
void displayOrder() const;

Owner: Josh.

8.11 OrderManager.h / OrderManager.cpp

Purpose:

Stores and manages all orders.

Fields:

vector<Order> orders;
int nextOrderId;

Important methods:

Order createOrder(int customerId, Cart& cart, ProductManager& productManager);
void addOrder(const Order& order);
vector<Order> getOrdersByCustomerId(int customerId) const;
const vector<Order>& getAllOrders() const;
int generateOrderId();
void displayOrdersByCustomerId(int customerId) const;

Owner: Josh.

8.12 Interaction.h / Interaction.cpp

Purpose:

Represents one user behavior record.

Fields:

int customerId;
int productId;
string type; // "view" or "purchase"
int count;

Important methods:

Interaction();
Interaction(int customerId, int productId, string type, int count);
int getCustomerId() const;
int getProductId() const;
string getType() const;
int getCount() const;
void incrementCount();

Owner: HX, because it supports recommendation and statistics.

8.13 RecommendationEngine.h / RecommendationEngine.cpp

Purpose:

Computes Top N recommended products.

Important methods:

double calculateScore(const Product& product,
                      const vector<int>& viewedProductIds,
                      const vector<int>& purchasedProductIds,
                      const ProductManager& productManager) const;
vector<Product> recommendTopN(const vector<Product>& products,
                              const vector<int>& viewedProductIds,
                              const vector<int>& purchasedProductIds,
                              int n) const;
bool hasPurchasedProduct(int productId, const vector<int>& purchasedProductIds) const;
bool hasCategoryMatch(const Product& product,
                      const vector<int>& historyProductIds,
                      const vector<Product>& products) const;

Owner: HX.

8.14 StatisticsManager.h / StatisticsManager.cpp

Purpose:

Computes admin statistics.

Important methods:

vector<Product> getMostViewedProducts(const vector<Product>& products, int limit) const;
vector<Product> getBestSellingProducts(const vector<Product>& products, int limit) const;
vector<pair<int, int>> getActiveUsers(const vector<Interaction>& interactions, int limit) const;
void displayMostViewedProducts(const vector<Product>& products, int limit) const;
void displayBestSellingProducts(const vector<Product>& products, int limit) const;
void displayActiveUsers(const vector<Interaction>& interactions, int limit) const;

Owner: HX.

8.15 FileManager.h / FileManager.cpp

Purpose:

Loads and saves data from files.

Important methods:

void loadProducts(ProductManager& productManager, string filename);
void saveProducts(const ProductManager& productManager, string filename);
void loadUsers(vector<Customer>& customers, vector<Admin>& admins, string filename);
void saveUsers(const vector<Customer>& customers, const vector<Admin>& admins, string filename);
void loadOrders(OrderManager& orderManager, string filename);
void saveOrders(const OrderManager& orderManager, string filename);
void loadInteractions(vector<Interaction>& interactions, string filename);
void saveInteractions(const vector<Interaction>& interactions, string filename);

Owner: HX.

8.16 Utils.h / Utils.cpp

Purpose:

Small helper functions used by many classes.

Possible methods:

vector<string> split(string line, char delimiter);
string getCurrentDateTime();
int getValidatedInt(string prompt);
double getValidatedDouble(string prompt);
string trim(string text);

Owner: Shared, but ideally HX if they are doing file parsing.

9. Data File Formats

9.1 products.txt

Recommended format:

id|name|category|price|stock|viewCount|purchaseCount

Example:

1|Wireless Mouse|Electronics|15.99|50|12|4
2|Mechanical Keyboard|Electronics|69.99|20|8|3
3|Notebook|Stationery|2.50|100|5|10

9.2 users.txt

Recommended format:

userId|name|email|password|role

Example:

1|Josh|josh@email.com|1234|customer
2|Admin|admin@email.com|admin123|admin

9.3 orders.txt

Recommended format:

orderId|customerId|dateTime|totalPrice|productId,productName,price,quantity;productId,productName,price,quantity

Example:

1|1|2026-05-31 10:30|85.98|1,Wireless Mouse,15.99,1;2,Mechanical Keyboard,69.99,1

9.4 interactions.txt

Recommended format:

customerId|productId|type|count

Example:

1|1|view|3
1|2|purchase|1
1|3|view|2

10. Workload Split

10.1 Josh’s Responsibilities

Josh owns the customer-side shopping system.

Files Josh should own:

include/Customer.h
src/Customer.cpp
include/CartItem.h
src/CartItem.cpp
include/Cart.h
src/Cart.cpp
include/OrderItem.h
src/OrderItem.cpp
include/Order.h
src/Order.cpp
include/OrderManager.h
src/OrderManager.cpp

Feature responsibilities:

* Customer menu.
* Product browsing from customer side.
* View product details.
* Increment product view count when product is viewed.
* Add product to cart.
* Remove product from cart.
* Update cart quantity.
* Display cart.
* Calculate cart total.
* Checkout.
* Create order from cart.
* Reduce stock after purchase.
* Increase product purchase count after purchase.
* Store purchased product IDs in customer history.
* Display customer order history.
* Connect customer menu to recommendation engine once HX finishes it.

Josh’s report sections:

* Customer features.
* Cart design.
* Checkout and order processing.
* Order history.
* Testing customer flow.

Josh’s demo section:

* Log in as customer.
* Browse products.
* View product details.
* Add product to cart.
* Update quantity.
* Checkout.
* View order history.
* Show recommendations after customer has interaction history.

10.2 HX’s Responsibilities

HX owns the admin, recommendation, statistics, and file persistence side.

Files HX should own:

include/ProductManager.h
src/ProductManager.cpp
include/Admin.h
src/Admin.cpp
include/Interaction.h
src/Interaction.cpp
include/RecommendationEngine.h
src/RecommendationEngine.cpp
include/StatisticsManager.h
src/StatisticsManager.cpp
include/FileManager.h
src/FileManager.cpp
include/Utils.h
src/Utils.cpp

Feature responsibilities:

* Admin menu.
* Add product.
* Edit product.
* Delete product.
* View all products.
* Most viewed products statistics.
* Best-selling products statistics.
* Active users statistics.
* Recommendation score calculation.
* Top N recommendation sorting.
* Category bonus logic.
* Load products from file.
* Save products to file.
* Load users from file.
* Save users to file.
* Load orders from file.
* Save orders to file.
* Load interactions from file.
* Save interactions to file.

HX’s report sections:

* Admin features.
* Product management.
* Recommendation engine.
* Scoring formula.
* Category bonus interpretation.
* File storage.
* Statistics.

HX’s demo section:

* Log in as admin.
* Add product.
* Edit product.
* Delete product.
* View most viewed products.
* View best-selling products.
* View active users.

10.3 Shared Responsibilities

These should be done together at the beginning:

include/Product.h
src/Product.cpp
include/User.h
src/User.cpp
src/main.cpp
README.md
initial data/*.txt files

Shared work:

* Agree on class names.
* Agree on method names.
* Agree on file formats.
* Create project skeleton.
* Create sample product data.
* Create sample users.
* Create compile instructions.
* Integrate both sides.
* Fix merge conflicts.
* Final testing.
* Final report editing.
* Demo rehearsal.

Important rule:

Only one person should edit main.cpp, Product.h, Product.cpp, User.h, and User.cpp at a time after the skeleton is created.

12. Implementation Milestones

Milestone 1: Skeleton and Interfaces

Goal:

All files exist. All class declarations exist. The program compiles even if most methods are empty.

Owners:

* Josh and HX together.

Deliverables:

* Folder structure.
* Header files.
* Empty source files.
* Basic main.cpp.
* Sample data files.

Milestone 2: Product and User Foundation

Goal:

Product and user objects work.

Deliverables:

* Product class complete.
* User, Customer, and Admin constructors compile.
* Product list can be displayed.

Owners:

* Shared.

Milestone 3: Customer Shopping Flow

Goal:

Customer can browse, add to cart, update cart, and checkout.

Deliverables:

* Cart works.
* Order creation works.
* Stock validation works.
* Purchase count updates.
* Customer order history works.

Owner:

* Josh.

Milestone 4: Admin and Product Management

Goal:

Admin can manage products.

Deliverables:

* Add product.
* Edit product.
* Delete product.
* View product list.

Owner:

* HX.

Milestone 5: File Persistence

Goal:

Data remains after closing the program.

Deliverables:

* Load products.
* Save products.
* Load users.
* Save users.
* Load orders.
* Save orders.
* Load interactions.
* Save interactions.

Owner:

* HX.

Milestone 6: Recommendation and Statistics

Goal:

Smart features work.

Deliverables:

* View interactions are recorded.
* Purchase interactions are recorded.
* Recommendation formula works.
* Category bonus works.
* Top N products are sorted correctly.
* Most viewed products works.
* Best-selling products works.
* Active users works.

Owner:

* HX.

Milestone 7: Integration and Polish

Goal:

The full system works smoothly.

Deliverables:

* Customer flow and admin flow connected through main.cpp.
* No major crashes from invalid input.
* Menus are clear.
* Demo data is prepared.
* README is complete.
* Report is complete.

Owners:

* Shared.

13. Acceptance Criteria

The project is considered complete when the following are true:

Customer Requirements

* Customer can browse products.
* Customer can view product details.
* Viewing a product increases view count.
* Customer can add item to cart.
* Customer can remove item from cart.
* Customer can update quantity.
* Customer can checkout.
* Checkout calculates total price correctly.
* Checkout reduces stock.
* Checkout increases purchase count.
* Checkout creates order history.
* Customer can view previous orders.
* Customer can receive Top N recommendations.

Admin Requirements

* Admin can add products.
* Admin can edit products.
* Admin can delete products.
* Admin can view all products.
* Admin can view most viewed products.
* Admin can view best-selling products.
* Admin can view active users.

Recommendation Requirements

* Uses the required formula.
* Uses view count.
* Uses purchase count.
* Uses category bonus.
* Sorts products by score descending.
* Returns Top N products.

File Storage Requirements

* Products are loaded from file.
* Products are saved to file.
* Orders are saved to file.
* Interactions are saved to file.
* Data does not disappear after restarting the program.

OOP Requirements

* Data members are private or protected where appropriate.
* Classes are separated into .h and .cpp files.
* Customer and Admin inherit from User.
* Cart uses CartItem.
* Order uses OrderItem.
* Recommendation logic is separated into RecommendationEngine.
* Statistics logic is separated into StatisticsManager.
* File logic is separated into FileManager.

14. Manual Test Plan

Test 1: Browse Product

Steps:

1. Log in as customer.
2. Display all products.
3. View details for product ID 1.
4. Exit and log in as admin.
5. Check most viewed products.

Expected result:

* Product ID 1 has increased view count.

Test 2: Add to Cart

Steps:

1. Log in as customer.
2. Add product ID 1 with quantity 2.
3. View cart.

Expected result:

* Cart displays product ID 1 with quantity 2.
* Total price is correct.

Test 3: Update Cart Quantity

Steps:

1. Add product ID 1 with quantity 2.
2. Update quantity to 3.
3. View cart.

Expected result:

* Cart shows quantity 3.
* Total price updates correctly.

Test 4: Checkout

Steps:

1. Add product to cart.
2. Checkout.
3. View order history.

Expected result:

* Order is created.
* Cart is cleared.
* Product stock decreases.
* Product purchase count increases.
* Order appears in order history.

Test 5: Invalid Stock

Steps:

1. Add product quantity greater than stock.
2. Try to checkout.

Expected result:

* System rejects checkout or asks for a valid quantity.
* Program does not crash.

Test 6: Recommendation Engine

Steps:

1. Customer views products in Electronics.
2. Customer purchases one Electronics product.
3. Ask for Top 3 recommendations.

Expected result:

* Products in Electronics receive category bonus.
* Products are sorted by score.
* Already purchased products are excluded.

Test 7: Admin Add Product

Steps:

1. Log in as admin.
2. Add a new product.
3. Display all products.

Expected result:

* New product appears in product list.

Test 8: Admin Edit Product

Steps:

1. Log in as admin.
2. Edit product price.
3. Display product details.

Expected result:

* Product price is updated.

Test 9: Admin Delete Product

Steps:

1. Log in as admin.
2. Delete a test product.
3. Display all products.

Expected result:

* Deleted product no longer appears.

Test 10: File Persistence

Steps:

1. Add product or checkout order.
2. Exit program.
3. Restart program.
4. Check data again.

Expected result:

* Changes still exist.

15. Demo Script

Part 1: Customer Demo — Josh

1. Start program.
2. Log in as customer.
3. Browse all products.
4. View details of one product.
5. Add product to cart.
6. Update quantity.
7. View cart.
8. Checkout.
9. View order history.
10. Ask for Top 3 recommendations.
11. Explain why those recommendations appeared.

Part 2: Admin Demo — HX

1. Log in as admin.
2. Add a new product.
3. Edit product price or stock.
4. Delete a test product.
5. View most viewed products.
6. View best-selling products.
7. View active users.
8. Exit and show that data was saved.

16. Report Structure

Recommended report sections:

1. Introduction
2. Project Requirements
3. System Design
4. Class Structure
5. OOP Principles Used
6. Customer Features
7. Admin Features
8. Shopping Cart and Order Processing
9. Recommendation Engine
10. File Storage
11. Statistics
12. Testing
13. Limitations
14. Future Improvements
15. Conclusion

Josh writes:

6. Customer Features
8. Shopping Cart and Order Processing
Customer-side testing cases
Customer-side demo screenshots

HX writes:

7. Admin Features
9. Recommendation Engine
10. File Storage
11. Statistics
Admin/recommendation/file testing cases
Admin-side demo screenshots

Shared final editing:

1. Introduction
2. Project Requirements
3. System Design
4. Class Structure
5. OOP Principles Used
13. Limitations
14. Future Improvements
15. Conclusion

17. README Structure

The README.md should contain:

Project title
Short description
Team members and responsibilities
How to compile
How to run
Default customer login
Default admin login
Data file explanation
Feature list
Known limitations

Example compile command:

g++ -std=c++17 src/*.cpp -Iinclude -o ecommerce
./ecommerce

18. Merge Rules

To avoid double work and merge conflicts:

1. Do not both edit the same file at the same time.
2. Keep main.cpp small.
3. Agree on method names before implementation.
4. Commit small changes often.
5. Pull the latest dev before starting work.
6. Merge into dev only after your part compiles.
7. Do not rewrite another person’s class without asking.
8. Use clear commit messages.
9. Test after every merge.
10. Keep backup copies of data files before changing file formats.

19. Highest-Score Enhancements

If there is extra time, add these features:

* Product search by keyword.
* Product filter by category.
* Product sorting by price.
* Low-stock warning for admin.
* Better active user display with customer names instead of only IDs.
* Clear recommendation explanation showing each product’s score.
* Input validation helper functions.
* Better formatted receipt after checkout.
* Save order receipt to file.
* Prevent duplicate product IDs.
* Prevent negative prices and negative stock.

20. Final Priority Order

If time becomes limited, prioritize in this order:

1. Product class and product list.
2. Customer browse products.
3. Cart add/remove/update.
4. Checkout and order history.
5. Admin add/edit/delete products.
6. File storage.
7. Recommendation engine.
8. Statistics.
9. Report and demo polish.

Do not spend too much time on fancy menus before the required logic works.