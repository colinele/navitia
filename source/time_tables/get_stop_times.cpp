#include "get_stop_times.h"
#include "routing/best_stoptime.h"
#include "type/pb_converter.h"
namespace navitia { namespace timetables {

std::vector<datetime_stop_time> get_stop_times(const std::vector<type::idx_t> &journey_pattern_points, const DateTime &dt,
                                               const DateTime &max_dt,
                                               const size_t max_departures, const type::Data & data, bool disruption_active,
                                               boost::optional<const std::string> calendar_id,
                                               const type::AccessibiliteParams & accessibilite_params) {
    std::vector<datetime_stop_time> result;
    auto test_add = true;

    // Prochain horaire où l’on demandera le prochain départ : on s’en sert pour ne pas obtenir plusieurs fois le même stop_time
    // Initialement, c’est l’heure demandée
    std::map<type::idx_t, DateTime> next_requested_datetime;
    for(auto jpp_idx : journey_pattern_points){
        next_requested_datetime[jpp_idx] = dt;
    }

    while(test_add && result.size() < max_departures) {
        test_add = false;
        for(auto jpp_idx : journey_pattern_points) {
            const type::JourneyPatternPoint* jpp = data.pt_data->journey_pattern_points[jpp_idx];
            if(!jpp->stop_point->accessible(accessibilite_params.properties)) {
                continue;
            }
            auto st = routing::earliest_stop_time(jpp, next_requested_datetime[jpp_idx], data, disruption_active, false, calendar_id, accessibilite_params.vehicle_properties);
            if(st.first != nullptr) {
                DateTime dt_temp = st.second;
                if(dt_temp <= max_dt && result.size() < max_departures) {
                    result.push_back(std::make_pair(dt_temp, st.first));
                    test_add = true;
                    // Le prochain horaire observé doit être au minimum une seconde après
                    if(st.first->is_frequency()) {
                        DateTimeUtils::update(dt_temp, st.first->end_time);
                    }
                    next_requested_datetime[jpp_idx] = dt_temp + 1;
                }
            }
        }
     }
    std::sort(result.begin(), result.end(),[](datetime_stop_time dst1, datetime_stop_time dst2) {return dst1.first < dst2.first;});

    return result;
}

}} // namespace navitia::timetables
