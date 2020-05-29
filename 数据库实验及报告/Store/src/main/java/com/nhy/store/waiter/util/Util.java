package com.nhy.store.waiter.util;

import com.nhy.store.waiter.model.Customer;
import org.springframework.security.core.context.SecurityContextHolder;

public class Util {
    public static Customer getCurrentUser() {
        Customer user = (Customer) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        return user;
    }
}
