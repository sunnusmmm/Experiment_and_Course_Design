package com.nhy.demo.mall.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import com.nhy.demo.mall.dao.ClassificationDao;
import com.nhy.demo.mall.entity.Classification;
import com.nhy.demo.mall.service.ClassificationService;

import java.util.List;

@Service
public class ClassificationServiceImpl implements ClassificationService {
    @Autowired
    private ClassificationDao classificationDao;

    @Override
    public Classification findById(int id) {
        return classificationDao.getOne(id);
    }

    @Override
    public List<Classification> findAll(int type) {
        return classificationDao.findByType(type);
    }

    @Override
    public Page<Classification> findAll(int type, Pageable pageable) {
        return classificationDao.findByType(type, pageable);
    }

    @Override
    public void update(Classification classification) {
        classificationDao.save(classification);
    }

    @Override
    public int create(Classification classification) {
        Classification classification1 = classificationDao.save(classification);
        return classification1.getId();
    }

    @Override
    public void delById(int id) {
        classificationDao.deleteById(id);
    }
}
