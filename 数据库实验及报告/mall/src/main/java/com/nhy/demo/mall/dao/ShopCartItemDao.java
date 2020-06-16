package com.nhy.demo.mall.dao;

import com.nhy.demo.mall.entity.ShopCartItem;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ShopCartItemDao extends JpaRepository<ShopCartItem, Integer> {

    List<ShopCartItem> findByUserid(int user_id);
    void deleteByUseridAndProductid(int user_id, int product_id);
}
