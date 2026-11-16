/**
 * @file MergeSortTests.cpp
 * @brief Testy jednostkowe klasy MergeSort z użyciem Google Test.
 *
 * Każdy test sprawdza osobny przypadek z treści zadania.
 * Oczekiwane wyniki są przygotowywane niezależnie od testowanej implementacji,
 * a dla dużych i losowych danych do ich wyznaczenia używany jest std::sort.
 */

#include <algorithm>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "MergeSort.h"

/**
 * @brief Sprawdza, czy już posortowany rosnąco wektor pozostaje niezmieniony.
 */
TEST(MergeSortTests, KeepsAlreadySortedArrayUnchanged)
{
    std::vector<int> values = { -10, -4, 0, 3, 8, 15 };
    const std::vector<int> original = values;

    MergeSort<int> sorter;
    sorter.sort(values);

    EXPECT_EQ(values, original);
}

/**
 * @brief Sprawdza sortowanie wektora ułożonego w kolejności malejącej.
 */
TEST(MergeSortTests, SortsReverseOrderedArray)
{
    std::vector<int> values = { 9, 7, 5, 3, 1, -1, -3 };
    const std::vector<int> expected = { -3, -1, 1, 3, 5, 7, 9 };

    MergeSort<int> sorter;
    sorter.sort(values);

    EXPECT_EQ(values, expected);
}

/**
 * @brief Sprawdza sortowanie losowej tablicy liczb.
 *
 * Stałe ziarno generatora zapewnia powtarzalność testu przy każdym uruchomieniu.
 */
TEST(MergeSortTests, SortsRandomArray)
{
    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-1000, 1000);

    std::vector<int> values(80);
    for (int& value : values)
    {
        value = distribution(generator);
    }

    std::vector<int> expected = values;
    std::sort(expected.begin(), expected.end());

    MergeSort<int> sorter;
    sorter.sort(values);

    EXPECT_EQ(values, expected);
}