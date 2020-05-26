package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.controller.request.NewOrderRequest;
import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.model.CommodityOrder;
import com.nhy.store.waiter.service.CommodityOrderService;
import com.nhy.store.waiter.service.CommodityService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/order")
@Slf4j
public class CommodityOrderController {
    @Autowired
    private CommodityOrderService orderService;
    @Autowired
    private CommodityService commodityService;

    @PostMapping("/")
    @ResponseStatus(HttpStatus.CREATED)
    public CommodityOrder create(@RequestBody NewOrderRequest newOrder) {
        log.info("Receive new Order {}", newOrder);
        Commodity[] commodityList = commodityService.getCommodityByName(newOrder.getItems())
                .toArray(new Commodity[]{});
        return orderService.createOrder(newOrder.getCustomer(), commodityList);
    }
}
