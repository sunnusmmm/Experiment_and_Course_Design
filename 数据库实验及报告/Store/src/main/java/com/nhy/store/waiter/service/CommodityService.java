package com.nhy.store.waiter.service;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.repository.CommodityRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheConfig;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@Slf4j
@CacheConfig(cacheNames = "CoffeeCache")
public class CommodityService {
    @Autowired
    private CommodityRepository commodityRepository;

    @Cacheable
    public List<Commodity> getAllCommodity() {
        return commodityRepository.findAll(Sort.by("id"));
    }

    public List<Commodity> getCommodityByName(List<String> names) {
        return commodityRepository.findByNameInOrderById(names);
    }
}
