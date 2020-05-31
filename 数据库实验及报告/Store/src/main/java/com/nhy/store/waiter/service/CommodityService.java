package com.nhy.store.waiter.service;

import com.nhy.store.waiter.model.Commodity;
import com.nhy.store.waiter.repository.CommodityRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheConfig;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.data.domain.Example;
import org.springframework.data.domain.ExampleMatcher;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

import static org.springframework.data.domain.ExampleMatcher.GenericPropertyMatchers.exact;

@Service
@Slf4j
@CacheConfig(cacheNames = "GoodsCache")
public class CommodityService {
    @Autowired
    private CommodityRepository commodityRepository;

    //    @Cacheable
    public List<Commodity> getAllCommodity() {
        return commodityRepository.findAll(Sort.by("id"));
    }

    public List<Commodity> getCommodityByName(List<String> names) {
        return commodityRepository.findByNameInOrderById(names);
    }

    public List<Commodity> findCommodityLike(String name) {
        return commodityRepository.findByNameLike("%" + name + "%");
    }

    public List<Commodity> getCommodityByType(String type) {
        return commodityRepository.findByTypeOrderById(type);
    }

    public boolean updateCommodity(Commodity commodity) {
        commodityRepository.save(commodity);
        return true;
    }

    public Optional<Commodity> getCommodityById(Long id) {
        return commodityRepository.findById(id);
    }

    public List<Commodity> getAllById(List<Integer> ids){
        return commodityRepository.findByIdIn(ids);
    }

    public boolean deleteCommodity(Long Id) {
        commodityRepository.deleteById(Id);
        return true;
    }
}
