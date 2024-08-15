#include <Common.h>
#include <Havoc.h>
#include <api/HcListener.h>

auto HcListenerProtocolData(
    const std::string& protocol
) -> json {

    for ( auto& p : Havoc->Gui->PageListener->Protocols ) {
        if ( p.contains( "data" ) ) {
            if ( p[ "data" ].contains( "protocol" ) ) {
                if ( p[ "data" ][ "protocol" ] == protocol ) {
                    if ( p[ "data" ].contains( "data" ) ) {
                        return p[ "data" ][ "data" ];
                    }
                }
            }
        }
    }

    return {};
}

auto HcListenerAll(
    void
) -> std::vector<std::string> {
    return Havoc->Listeners();
}

auto HcListenerQueryType(
    const std::string& name
) -> std::string {
    for ( auto& n : Havoc->Listeners() ) {
        if ( auto obj = Havoc->ListenerObject( n ) ) {
            if ( obj.has_value() && obj.value()[ "name" ] == name ) {
                return obj.value()[ "protocol" ].get<std::string>();
            }
        }
    }

    return std::string();
}