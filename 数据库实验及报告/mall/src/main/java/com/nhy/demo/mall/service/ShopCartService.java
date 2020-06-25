package com.nhy.demo.mall.service;

import com.nhy.demo.mall.entity.OrderItem;
import com.nhy.demo.mall.entity.ShopCartItem;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * 购物车
 */
public interface ShopCartService {

    String NAME_PREFIX = "shop_cart_";

    List<OrderItem> listCart(HttpServletRequest request) throws Exception;

    void add(int product_id, HttpServletRequest request)throws Exception;

    void delete(int product_id, HttpServletRequest request)throws Exception;
}
