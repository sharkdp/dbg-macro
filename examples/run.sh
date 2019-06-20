#!/bin/bash

trigger 'make && ./test_dbg_macro' Makefile test_dbg_macro.cpp ../dbg.h
