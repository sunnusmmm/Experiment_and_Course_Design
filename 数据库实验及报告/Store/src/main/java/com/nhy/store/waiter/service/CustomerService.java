package com.nhy.store.waiter.service;

import com.nhy.store.waiter.model.Customer;
import com.nhy.store.waiter.repository.CustomerRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
@Slf4j
public class CustomerService {
    @Autowired
    private CustomerRepository customerRepository;

    public boolean addCustomerInfro(Customer customer) {
        customerRepository.save(customer);
        return true;
    }

    public boolean updateInfo(Customer customer) {
        customerRepository.save(customer);
        return true;
    }

    public Customer getByName(String name) {
        return customerRepository.findByName(name);
    }
}
