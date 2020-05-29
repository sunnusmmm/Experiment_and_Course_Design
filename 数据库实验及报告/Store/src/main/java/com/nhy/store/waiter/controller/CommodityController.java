package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.service.CommodityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@RestController
@RequestMapping("/goods")
public class CommodityController {
    @Autowired
    private CommodityService commodityService;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public ModelAndView getAll() {
        List<Commodity> list = commodityService.getAllCommodity();
        ModelAndView view = new ModelAndView("Commodity");
        view.addObject("commodityList",list);
        return view;
    }

    @RequestMapping(value = "/name/{name}", method = RequestMethod.GET)
    public List<Commodity> getByName(@PathVariable String name) {
        return commodityService.findCommodityLike(name);
    }

    @RequestMapping(value = "/type/{type}", method = RequestMethod.GET)
    public List<Commodity> getByType(@PathVariable String type) {
        return commodityService.getCommodityByType(type);
    }

    @RequestMapping(value = "/update", method = RequestMethod.POST)
    public boolean getByType(@RequestBody Commodity commodity) {
        return commodityService.updateCommodity(commodity);
    }

    @RequestMapping(value = "/delete", method = RequestMethod.DELETE)
    public boolean deleteByName(@RequestBody Commodity commodity) {
        return commodityService.deleteCommodity(commodity);
    }
}
