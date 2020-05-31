package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.service.CommodityService;
import com.nhy.store.waiter.util.Util;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;
import java.util.Optional;

@Controller
@RequestMapping("/goods")
public class CommodityController {
    @Autowired
    private CommodityService commodityService;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public ModelAndView getAll() {
        List<Commodity> list = commodityService.getAllCommodity();
        ModelAndView view = new ModelAndView("Commodity");
        view.addObject("uid", Util.getCurrentUser().getUsername());
        view.addObject("name", Util.getCurrentUser().getPassword());
        view.addObject("commodityList", list);
        return view;
    }

    @GetMapping("/add")
    public ModelAndView createForm(Model model) {
        model.addAttribute("commodity", new Commodity());
        model.addAttribute("title", "创建商品");
        return new ModelAndView("addCommodity", "userModel", model);
    }


    @RequestMapping(value = "/add", method = RequestMethod.POST)
    public ModelAndView saveCommodity(Commodity commodity) {
        commodityService.updateCommodity(commodity);
        return new ModelAndView("redirect:/goods/");//重定向到list页面
    }

    @RequestMapping(value = "/name/{name}", method = RequestMethod.GET)
    public ModelAndView getByName(@PathVariable String name) {
        List<Commodity> list = commodityService.findCommodityLike(name);
        ModelAndView view = new ModelAndView("Commodity");
        view.addObject("uid", Util.getCurrentUser().getUsername());
        view.addObject("name", Util.getCurrentUser().getPassword());
        view.addObject("commodityList", list);
        return view;
    }

    @RequestMapping(value = "/type/{type}", method = RequestMethod.GET)
    public List<Commodity> getByType(@PathVariable String type) {
        return commodityService.getCommodityByType(type);
    }

    @GetMapping("/update/{id}")
    public ModelAndView updateForm(@PathVariable Long id, Model model) {
        Commodity commodity = commodityService.getCommodityById(id).get();
        ModelAndView view = new ModelAndView("addCommodity");
        view.addObject("id",commodity.getId());
        view.addObject("type",commodity.getType());
        view.addObject("name",commodity.getName());
        view.addObject("price",commodity.getPrice());
        view.addObject("discount",commodity.getDiscount());
        view.addObject("description",commodity.getDescription());
        view.addObject("createTime",commodity.getCreateTime());
        view.addObject("updateTime",commodity.getUpdateTime());
        return view;
    }

    @RequestMapping(value = "/update/{id}", method = RequestMethod.POST)
    public ModelAndView updateCommodity(@PathVariable Long id, Commodity commodity) {
//        commodity.setId(id);
        commodityService.updateCommodity(commodity);
        return new ModelAndView("redirect:/goods/");
    }

    @RequestMapping(value = "/delete/{id}")
    public String deleteByName(@PathVariable Long id) {
        commodityService.deleteCommodity(id);
        return "redirect:/goods/";
    }
}
