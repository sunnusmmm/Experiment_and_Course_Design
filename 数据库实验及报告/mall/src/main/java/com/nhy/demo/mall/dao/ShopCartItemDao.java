package com.nhy.demo.mall.dao;

import com.nhy.demo.mall.entity.ShopCartItem;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ShopCartItemDao extends JpaRepository<ShopCartItem, Integer> {
    //根据用户ID查找其购物车商品
    List<ShopCartItem> findByUserid(int user_id);
    //根据用户ID、商品ID删除商品
    void deleteByUseridAndProductid(int user_id, int product_id);
}
