package com.nhy.demo.mall.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import com.nhy.demo.mall.dao.ClassificationDao;
import com.nhy.demo.mall.dao.ProductDao;
import com.nhy.demo.mall.entity.Classification;
import com.nhy.demo.mall.entity.Product;
import com.nhy.demo.mall.service.ProductService;

import java.util.ArrayList;
import java.util.List;

@Service
public class ProductServiceImpl implements ProductService {
    @Autowired
    private ProductDao productDao;
    @Autowired
    private ClassificationDao classificationDao;

    @Override
    public Product findById(int id) {
        return productDao.getOne(id);
    }

    @Override
    public Page<Product> findAll(Pageable pageable) {
        return productDao.findAll(pageable);
    }

    @Override
    public List<Product> findHotProduct() {
        return productDao.findByIsHot(1, null);
    }

    @Override
    public List<Product> findByCid(int cid, Pageable pageable) {
        List<Classification> sec = classificationDao.findById(cid);
        List<Integer> secIds = new ArrayList<>();
        for (Classification classification : sec) {
            secIds.add(classification.getId());
        }
        return productDao.findByCsidIn(secIds,pageable);
    }

    @Override
    public void update(Product product) {
        productDao.save(product);
    }

    @Override
    public int create(Product product) {
        return productDao.save(product).getId();
    }

    @Override
    public void delById(int id) {
        productDao.deleteById(id);
    }
}
