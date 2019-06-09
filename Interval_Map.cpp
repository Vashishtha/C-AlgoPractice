#include <map>
#include <limits>

template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		if (!( keyBegin < keyEnd ))//empty interval check
		{
			return;		
		}
		
		auto lbegin = m_map.lower_bound(keyBegin);
		auto lend = m_map.lower_bound(keyEnd);
		if(lbegin != m_map.begin() &&
		   (--lbegin)->second == val)// to check if key less than keyBegin contain same value
		{
		    return;
		}   
		else if(((lend == m_map.end() || keyEnd < lend->first) && (std::prev(lend)->second == val)) && 
		        (lend->second == val))//To check if key greater than key begin contain same value
		{
		    return;
		}
		
		//if yes in any of case than return because we want diff value in every range
		
		auto upper_end = m_map.upper_bound(keyEnd);
		if(upper_end == m_map.begin())//if start of map key is larger than keyEnd
		{
			upper_end = m_map.insert(m_map.begin(),std::make_pair(keyEnd,m_map.begin()->second));
		}
		
		else//if either at end or at key value greater than keyEnd but not begin
		{
			auto last_value = std::prev(upper_end)->second;
			upper_end = m_map.insert(upper_end,std::make_pair(keyEnd,std::move(last_value)));
		}
		
		auto lower_end = m_map.lower_bound(keyBegin);//either same as keyEnd or smaller than that or equal to keyBegin
		
		m_map.erase(lower_end,upper_end);//remove exsisting records with old values for limit
		m_map.emplace_hint(upper_end, std::move(keyBegin), std::move(val));
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.
