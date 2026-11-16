/**
 * @file MergeSort.h
 * @brief Szablonowa implementacja algorytmu sortowania przez scalanie (Merge Sort).
 *
 * Klasa jest przeznaczona do sortowania elementów przechowywanych w std::vector.
 * Można jej używać między innymi dla typów int, long int, float i double.
 */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <cstddef>
#include <vector>

/**
 * @brief Klasa implementująca stabilny algorytm sortowania przez scalanie.
 *
 * @tparam T Typ elementów sortowanej tablicy. Typ powinien obsługiwać operator <,
 *           konstrukcję domyślną oraz przypisanie. Typowe typy liczbowe C++
 *           (int, long int, float, double itd.) spełniają te wymagania.
 *
 * Algorytm sortuje elementy rosnąco. Sortowanie odbywa się bezpośrednio
 * w przekazanym wektorze.
 *
 * Złożoność czasowa: O(n log n).
 * Złożoność pamięciowa: O(n) dodatkowej pamięci na bufor pomocniczy.
 */
template <typename T>
class MergeSort
{
public:
    /**
     * @brief Sortuje elementy wektora rosnąco.
     *
     * Dla pustego wektora i wektora zawierającego jeden element metoda
     * natychmiast kończy działanie. Nie jest wtedy zgłaszany wyjątek.
     *
     * @param values Wektor, którego elementy mają zostać posortowane.
     */
    void sort(std::vector<T>& values) const
    {
        // dla 0 albo 1 argumentu nie bedzie sie uruchaiac
        if (values.size() < 2)
        {
            return;
        }

        // jeden bufor pomocniczy wykorzystywany do calego sortowania
        std::vector<T> buffer(values.size());
        mergeSort(values, buffer, 0, values.size() - 1);
    }

private:
    /**
     * @brief Rekurencyjnie dzieli fragment wektora i scala jego posortowane części.
     *
     * @param values Sortowany wektor.
     * @param buffer Bufor pomocniczy o rozmiarze równym rozmiarowi wektora.
     * @param left Indeks pierwszego elementu sortowanego fragmentu.
     * @param right Indeks ostatniego elementu sortowanego fragmentu.
     */
    void mergeSort(std::vector<T>& values,
                   std::vector<T>& buffer,
                   std::size_t left,
                   std::size_t right) const
    {
        // fragment z posortowanym jednym elementem
        if (left >= right)
        {
            return;
        }

        // obliczanie srodka bez ryzyka przepelnienia
        const std::size_t middle = left + (right - left) / 2;

        // sortowanie lewej i prawej polowy
        mergeSort(values, buffer, left, middle);
        mergeSort(values, buffer, middle + 1, right);

        // laczenie w jedna calasc dwoch posortowanych polowek
        merge(values, buffer, left, middle, right);
    }

    /**
     * @brief Scala dwa sąsiadujące, wcześniej posortowane fragmenty wektora.
     *
     * @param values Sortowany wektor.
     * @param buffer Bufor pomocniczy.
     * @param left Indeks początku lewego fragmentu.
     * @param middle Indeks końca lewego fragmentu.
     * @param right Indeks końca prawego fragmentu.
     */
    void merge(std::vector<T>& values,
               std::vector<T>& buffer,
               std::size_t left,
               std::size_t middle,
               std::size_t right) const
    {
        std::size_t leftIndex = left;
        std::size_t rightIndex = middle + 1;
        std::size_t outputIndex = left;

        
        // wybranie mniejszego elementu z dwch polowek i zapisanie go do bufora
        while (leftIndex <= middle && rightIndex <= right)
        {
            if (!(values[rightIndex] < values[leftIndex]))
            {
                buffer[outputIndex++] = values[leftIndex++];
            }
            else
            {
                buffer[outputIndex++] = values[rightIndex++];
            }
        }

        // przypisanie elementow ktore zostaly w lewej polowie
        while (leftIndex <= middle)
        {
            buffer[outputIndex++] = values[leftIndex++];
        }

        // przyisanie elementow ktore zostaly z prawej strony
        while (rightIndex <= right)
        {
            buffer[outputIndex++] = values[rightIndex++];
        }

        // zapisanie scalonego elementu z bufora do wektora
        for (std::size_t i = left; i <= right; ++i)
        {
            values[i] = buffer[i];
        }
    }
};

#endif 
