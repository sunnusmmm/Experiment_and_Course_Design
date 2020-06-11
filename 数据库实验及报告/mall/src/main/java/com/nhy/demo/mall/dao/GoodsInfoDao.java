package com.nhy.demo.mall.dao;

import java.util.List;

import com.nhy.demo.mall.entity.GoodsInfo;

/**
 * 商品Dao层
 */
public interface GoodsInfoDao {
    /**
     * 插入商品信息
     * @param infos
     */
    void saveBatch(List<GoodsInfo> infos);
}