package com.nhy.store.waiter.util;

import com.nhy.store.waiter.model.User;
import org.springframework.security.core.context.SecurityContextHolder;

public class Util {
    public static User getCurrentUser() {
        User user = (User) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        return user;
    }
}