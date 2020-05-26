package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.service.CommodityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/coffee")
public class CommodityController {
    @Autowired
    private CommodityService commodityService;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public List<Commodity> getAll() {
        return commodityService.getAllCommodity();
    }

    @RequestMapping(value = "/{name}", method = RequestMethod.GET)
    public List<Commodity> getByName(@PathVariable List<String> name){
        return commodityService.getCommodityByName(name);
    }
}
