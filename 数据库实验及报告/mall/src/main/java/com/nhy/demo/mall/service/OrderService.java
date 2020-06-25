package com.nhy.demo.mall.service;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.nhy.demo.mall.entity.Order;
import com.nhy.demo.mall.entity.OrderItem;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

public interface OrderService {
    /**
     * 订单状态 1:未付款 2:等待发货 3:等待收货 4:订单完成
     */
    int STATE_NO_PAY = 1;
    int STATE_WAITE_SEND = 2;
    int STATE_WAIT_RECEIVE = 3;
    int STATE_COMPLETE = 4;

    //根据id查询
    Order findById(int id);

    //分页查询所有
    Page<Order> findAll(Pageable pageable);

    void update(Order order);

    int create(Order order);

    void delById(int id);

    //查询订单的订单项
    List<OrderItem> findItems(int orderId);

    //更改订单状态
    void updateStatus(int id, int status);

    //查找用户的订单列表
    List<Order> findUserOrder(HttpServletRequest request);

    //支付
    void pay(int orderId);

    //提交订单
    void submit(String name, String phone, String addr, HttpServletRequest request, HttpServletResponse response) throws Exception;

    //确认收货
    void receive(int orderId);
}
