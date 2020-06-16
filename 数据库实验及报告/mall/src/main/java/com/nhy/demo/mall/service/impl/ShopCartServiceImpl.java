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
import com.nhy.demo.mall.service.exception.LoginException;
import org.springframework.transaction.annotation.Transactional;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

@Service
public class ShopCartServiceImpl implements ShopCartService {

    @Autowired
    private ProductService productService;

    @Autowired
    private ShopCartItemDao shopCartItemDao;

    /**
     * 加购物车
     * 将商品id保存到Session中List<Integer>中
     *
     * @param productId
     * @param request
     */
    @Override
    public void addCart(int productId, HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
        List<Integer> productIds = (List<Integer>) request.getSession().getAttribute(NAME_PREFIX + loginUser.getId());
        if (productIds == null) {
            productIds = new ArrayList<>();
            request.getSession().setAttribute(NAME_PREFIX + loginUser.getId(), productIds);
        }
        productIds.add(productId);
    }

    /**
     * 移除
     * <p>
     * 移除session List中对应的商品Id
     *
     * @param productId
     * @param request
     */
    @Override
    @Transactional
    public void remove(int productId, HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
        List<Integer> productIds = (List<Integer>) request.getSession().getAttribute(NAME_PREFIX + loginUser.getId());
        Iterator<Integer> iterator = productIds.iterator();
        while (iterator.hasNext()) {
            if (productId == iterator.next()) {
                iterator.remove();
            }
        }
    }

    /**
     * 查看购物车
     * <p>
     * 查询出session的List中所有的商品Id,并封装成List<OrderItem>返回
     *
     * @param request
     * @return
     */
    @Override
    public List<OrderItem> listCart(HttpServletRequest request) throws Exception {
        User loginUser = (User) request.getSession().getAttribute("user");
        if (loginUser == null)
            throw new Exception("未登录！请重新登录");
//        List<Integer> productIds = (List<Integer>) request.getSession().getAttribute(NAME_PREFIX + loginUser.getId());
        List<ShopCartItem> shopCartItems = shopCartItemDao.findByUserid(loginUser.getId());
        List<Integer> productIds = new ArrayList<>();
        for (ShopCartItem shopCartItem :shopCartItems){
            productIds.add(shopCartItem.getProductid());
        }
        // key: productId value:OrderItem
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