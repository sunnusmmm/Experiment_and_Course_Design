package com.nhy.demo.mall.controller.user;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import com.nhy.demo.mall.entity.*;
import com.nhy.demo.mall.entity.pojo.ResultBean;
import com.nhy.demo.mall.service.*;

import javax.servlet.http.HttpServletRequest;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/product")
class ProductController {
    @Autowired
    private ProductService productService;
    @Autowired
    private ClassificationService classificationService;
    @Autowired
    private ShopCartService shopCartService;
    @Autowired
    private UserService userService;

    /**
     * 获取商品信息
     *
     * @param id
     * @return
     */
    @RequestMapping("/get.do")
    public ResultBean<Product> getProduct(int id) {
        Product product = productService.findById(id);
        return new ResultBean<>(product);
    }

    /**
     * 打开商品详情页面
     *
     * @param id
     * @param map
     * @return
     */
    @RequestMapping("/get.html")
    public String toProductPage(int id, Map<String, Object> map) {
        Product product = productService.findById(id);
        User user = userService.findById(id);
        map.put("product", product);
        map.put("user", user);

        return "mall/product/info";
    }

    /**
     * 查找热门商品
     *
     * @return
     */
    @ResponseBody
    @RequestMapping("/hot.do")
    public ResultBean<List<Product>> getHotProduct() {
        List<Product> products = productService.findHotProduct();
        return new ResultBean<>(products);
    }

    /**
     * 查找最新商品
     *
     * @param pageNo
     * @param pageSize
     * @return
     */
    @ResponseBody
    @RequestMapping("/new.do")
    public ResultBean<List<Product>> getNewProduct(int pageNo, int pageSize) {
//        Pageable pageable = new PageRequest(pageNo, pageSize);
        Pageable pageable = PageRequest.of(pageNo, pageSize);
//        List<Product> products = productService.findNewProduct(pageable);
        List<Product> products = productService.findAll(pageable).getContent();
        return new ResultBean<>(products);
    }

    /**
     * 打开分类查看商品页面
     *
     * @return
     */
    @RequestMapping("/category.html")
    public String toCatePage(int cid, Map<String, Object> map) {
        Classification classification = classificationService.findById(cid);
        map.put("category", classification);
        return "mall/product/category";
    }

    @RequestMapping("/toCart.html")
    public String toCart() {
        return "mall/product/cart";
    }

    /**
     * 按一级分类查找商品
     *
     * @param cid
     * @param pageNo
     * @param pageSize
     * @return
     */
    @ResponseBody
    @RequestMapping("/category.do")
    public ResultBean<List<Product>> getCategoryProduct(int cid, int pageNo, int pageSize) {
//        Pageable pageable = new PageRequest(pageNo, pageSize);
        Pageable pageable = PageRequest.of(pageNo, pageSize);
        List<Product> products = productService.findByCid(cid, pageable);
        return new ResultBean<>(products);
    }

    /**
     * 添加进入购物车
     *
     * @param productId
     * @param request
     * @return
     */
    @ResponseBody
    @RequestMapping("/addCart.do")
    public ResultBean<Boolean> addToCart(int productId, HttpServletRequest request) throws Exception {
//        shopCartService.addCart(productId, request);
        shopCartService.add(productId, request);
        return new ResultBean<>(true);
    }

    /**
     * 移除购物车
     *
     * @param productId
     * @param request
     * @return
     */
    @ResponseBody
    @RequestMapping("/delCart.do")
    public ResultBean<Boolean> delToCart(int productId, HttpServletRequest request) throws Exception {
//        shopCartService.remove(productId, request);
        shopCartService.delete(productId, request);
        return new ResultBean<>(true);
    }

    /**
     * 查看购物车商品
     *
     * @param request
     * @return
     */
    @ResponseBody
    @RequestMapping("/listCart.do")
    public ResultBean<List<OrderItem>> listCart(HttpServletRequest request) throws Exception {
        List<OrderItem> orderItems = shopCartService.listCart(request);
        return new ResultBean<>(orderItems);
    }
}