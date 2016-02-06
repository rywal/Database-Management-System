//
//  AttributeList.h
//
#ifndef AttributeList_h
#define AttributeList_h

#include <stdio.h>
#include <vector>
#include "Attribute.h"

// Collection of Attributes within the Relation
class AttributeList {
    public:
    vector<Attribute> attributes;
    AttributeList() { }

    int num_attributes() {
//        std::cout << "Attributes: " << attributes.size() << "\n";
        return attributes.size();
    }
    
    vector<string>  names(){
		vector<string> result;
		for (int i=0; i<num_attributes(); i++){
			result.push_back( attributes[i].get_name() );
		}
		return result;
	}
                                    
    vector<int> maxes(){
		vector<int> result;
		for (int i=0; i<num_attributes(); i++){
			result.push_back( attributes[i].get_max_length() );
		}
		return result;
	}
    
    vector<string> combine_names(AttributeList a, AttributeList b){
        vector<string> result;
        
        for(int i=0; i < a.num_attributes(); i++){
            result.push_back( a.attributes[i].get_name() );
        }
        
        for(int i=0; i < b.num_attributes(); i++){
            result.push_back( b.attributes[i].get_name() );
        }
        
        return result;
    }
    
    vector<int> combine_max( AttributeList a, AttributeList b){
        vector<int> result;
        
        for(int i=0; i < a.num_attributes(); i++){
            result.push_back( a.attributes[i].get_max_length() );
        }
        
        for(int i=0; i < b.num_attributes(); i++){
            result.push_back( b.attributes[i].get_max_length() );
        }
        
        return result;
    }
#endif /* AttributeList_h */
