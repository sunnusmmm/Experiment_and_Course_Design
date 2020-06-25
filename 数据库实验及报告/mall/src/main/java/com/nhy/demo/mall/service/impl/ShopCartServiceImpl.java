package com.nhy.demo.mall.service.impl;

import com.nhy.demo.mall.dao.ShopCartItemDao;
import com.nhy.demo.mall.entity.ShopCartItem;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.nhy.demo.mall.entity.OrderItem;
import com.nhy.demo.mall.entity.Product;
import com.nhy.demo.mall.entity.User;
import com.nhy.demo.mall.service.ProductService;
import com.nhy.demo.mall.service.ShopCartService;
import org.springframework.transaction.annotation.Transactional;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
public class ShopCartServiceImpl implements ShopCartService {

    @Autowired
    private ProductService productService;

    @Autowired
    private ShopCartItemDao shopCartItemDao;
    //查询所有订单项目
    @Override
    public List<OrderItem> listCart(HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
        List<ShopCartItem> shopCartItems = shopCartItemDao.findByUserid(loginUser.getId());
        List<Integer> productIds = new ArrayList<>();
        for (ShopCartItem shopCartItem :shopCartItems){
            productIds.add(shopCartItem.getProductid());
        }
        Map<Integer, OrderItem> productMap = new HashMap<>();
        if (productIds == null) {
            return new ArrayList<>();
        }
        // 遍历List中的商品id，每个商品Id对应一个OrderItem
        for (Integer productId : productIds) {
            if (productMap.get(productId) == null) {
                Product product = productService.findById(productId);
                OrderItem orderItem = new OrderItem();
                orderItem.setProduct(product);
                orderItem.setProductId(productId);
                orderItem.setCount(1);
                orderItem.setSubTotal(product.getShopPrice());
                productMap.put(productId, orderItem);
            } else {
                OrderItem orderItem = productMap.get(productId);
                int count = orderItem.getCount();
                orderItem.setCount(++count);
                Double subTotal = orderItem.getSubTotal();
                orderItem.setSubTotal(orderItem.getSubTotal() + subTotal);
                productMap.put(productId, orderItem);
            }
        }
        List<OrderItem> orderItems = new ArrayList<>(productMap.values());
        return orderItems;
    }

    @Override
    public void add(int product_id, HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
        ShopCartItem shopCartItem = new ShopCartItem();
        shopCartItem.setUserid(loginUser.getId());
        shopCartItem.setProductid(product_id);
        shopCartItemDao.save(shopCartItem);
    }

    @Override
    @Transactional
    public void delete(int product_id, HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
        shopCartItemDao.deleteByUseridAndProductid(loginUser.getId(), product_id);
    }
}