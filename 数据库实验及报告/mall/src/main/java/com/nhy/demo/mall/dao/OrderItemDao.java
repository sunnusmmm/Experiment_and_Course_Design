package com.nhy.demo.mall.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import com.nhy.demo.mall.entity.OrderItem;

import java.util.List;

public interface OrderItemDao extends JpaRepository<OrderItem, Integer> {
    //根据订单Id查询
    List<OrderItem> findByOrderId(int orderId);
}
