package com.nhy.store.waiter.service;

import com.nhy.store.waiter.repository.CommodityOrderRepository;
import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.model.CommodityOrder;
import com.nhy.store.waiter.model.OrderState;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.ArrayList;
import java.util.Arrays;

@Service
@Transactional
@Slf4j
public class CommodityOrderService {
    @Autowired
    private CommodityOrderRepository orderRepository;

    public CommodityOrder createOrder(String customer, Commodity... commodity) {
        CommodityOrder order = CommodityOrder.builder()
                .customer(customer)
                .items(new ArrayList<>(Arrays.asList(commodity)))
                .state(OrderState.INIT)
                .build();
        CommodityOrder saved = orderRepository.save(order);
        log.info("New Order: {}", saved);
        return saved;
    }

    public boolean updateState(CommodityOrder order, OrderState state) {
        if (state.compareTo(order.getState()) <= 0) {
            log.warn("Wrong State order: {}, {}", state, order.getState());
            return false;
        }
        order.setState(state);
        orderRepository.save(order);
        log.info("Updated Order: {}", order);
        return true;
    }
}
