package com.nhy.store.waiter.repository;

import com.nhy.store.waiter.model.Commodity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface CommodityRepository extends JpaRepository<Commodity, Long> {
    List<Commodity> findByNameInOrderById(List<String> list);

    Commodity findByName(String name);
}
