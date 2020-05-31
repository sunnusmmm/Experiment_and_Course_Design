package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.model.User;
import com.nhy.store.waiter.service.UserServiceDetil;
import com.nhy.store.waiter.util.Util;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    private UserServiceDetil userServiceDetil;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public ModelAndView getAll() {
        
        ModelAndView view = new ModelAndView("User");
        view.addObject("user", Util.getCurrentUser());
        return view;
    }

    @GetMapping("/reg")
    public ModelAndView createForm(Model model) {
        return new ModelAndView("reg");
    }

    @RequestMapping(value = "/reg", method = RequestMethod.POST)
    public ModelAndView saveCommodity(User user) {
        userServiceDetil.regUser(user);

        return new ModelAndView("redirect:/goods/");
    }
}
