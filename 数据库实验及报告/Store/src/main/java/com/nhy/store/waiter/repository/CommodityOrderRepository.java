package com.nhy.store.waiter.repository;

import com.nhy.store.waiter.model.CommodityOrder;
import org.springframework.data.jpa.repository.JpaRepository;

public interface CommodityOrderRepository extends JpaRepository<CommodityOrder, Long> {
}
