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

    /**
     * 加购物车
     *
     * @param
     */
    void addCart(int productId, HttpServletRequest request) throws Exception;

    /**
     * 移除
     *
     * @param productId
     * @param request
     */
    void remove(int productId, HttpServletRequest request) throws Exception;

    /**
     * 查看购物车
     *
     * @param request
     * @return
     */
    List<OrderItem> listCart(HttpServletRequest request) throws Exception;

    void add(int product_id, HttpServletRequest request)throws Exception;

    void delete(int product_id, HttpServletRequest request)throws Exception;
}
