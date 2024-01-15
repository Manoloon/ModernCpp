// when doing lazy initialization , we need to do a double checked lock to avoid data race , but we can face another data race due to obj construct order.
