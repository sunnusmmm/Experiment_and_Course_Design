package com.nhy.store.waiter.repository;

import com.nhy.store.waiter.model.Customer;
import org.springframework.data.jpa.repository.JpaRepository;

public interface CustomerRepository extends JpaRepository<Customer, Long> {
}
