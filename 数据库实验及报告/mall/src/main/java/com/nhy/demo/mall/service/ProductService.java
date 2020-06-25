package com.nhy.demo.mall.service;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.nhy.demo.mall.entity.Product;
import java.util.List;

public interface ProductService {
    //根据ID查询商品
    Product findById(int id);

    //查找所有商品
    Page<Product> findAll(Pageable pageable);

    //热门商品
    List<Product> findHotProduct();
    //按分类查找商品
    List<Product> findByCid(int cid,Pageable pageable);

    void update(Product product);
    int create(Product product);
    void delById(int id);
}
