package com.nhy.demo.mall.service;

import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.nhy.demo.mall.entity.Classification;

import java.util.List;

public interface ClassificationService {
    /**
     * 根据id查询
     *
     * @param id
     * @return
     */
    Classification findById(int id);

    /**
     * 按分类查询所有
     *
     * @param type
     * @return
     */
    List<Classification> findAll(int type);

    /**
     * 按分类查询所有
     *
     * @param pageable
     * @return
     */
    Page<Classification> findAll(int type,Pageable pageable);

    /**
     * 更新
     *
     * @param Classification
     * @return
     */
    void update(Classification Classification);

    /**
     * 创建
     *
     * @param Classification
     * @return
     */
    int create(Classification Classification);

    /**
     * 根据Id删除
     *
     * @param id
     * @return
     */
    void delById(int id);
}
