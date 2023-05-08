// A simple representation of graph using STL
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include <stdlib.h>
//#include <bits/stdc++.h>
#include <algorithm>    // std::min


using namespace std;

//This is the number of locations for our specific graph
//There are 6 locations in total
/*
Location 0: The Student Union, the starting and ending place for each robot
Location 1: The Honors Village
Location 2: The Global Center
Location 3: Science and Engineering Library
Location 4: Main Library
Location 5: Gittings Building

The algorithm is designed to nimize the effort needed to calculate the best possible path
for running multiple delivery robots at the same time.

To do this, we take advantange of the fact that the project description mentions
a KNOWN, BOUND terrain

What will be done is a system similar to network routers used in the internet protocol,
resulting in a problem similar to the travelling salesman problem

Each of the locations will hold a forwarding table, indicating which next location to go to
for the shortest possible path to that particular destination.
The forwarding table must be ketp up to date with road closures and stuff
Our assumption for this project is that no location becomes fully inaccessible ever.

Once this is established, robots will run a quick graph search/comparison to determine how
to distribute locations, and orders between them.

*/
#define NUM_LOCATIONS 6
#define NUM_ROBOTS 5
#define MAX_TOTAL_ORDERS 10
#define MAX_ROBOT_ORDERS 3

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
  
    // Initialize min value
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < NUM_LOCATIONS; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}
  
// A utility function to print the constructed distance
// array
void printSolution(int dist[])
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < NUM_LOCATIONS; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int graph[NUM_LOCATIONS][NUM_LOCATIONS], int src, int output[NUM_LOCATIONS][NUM_LOCATIONS])
{
    int dist[NUM_LOCATIONS]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i
  
    bool sptSet[NUM_LOCATIONS]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
  
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < NUM_LOCATIONS; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
  
    // Find shortest path for all vertices
    for (int count = 0; count < NUM_LOCATIONS - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet);
  
        // Mark the picked vertex as processed
        sptSet[u] = true;
  
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < NUM_LOCATIONS; v++)
  
            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
  
    // print the constructed distance array
    //printSolution(dist);
    //copy the results back to the main function
    for(int j = 0; j < NUM_LOCATIONS; j++){
            output[src][j] = dist[j];
    }
}

class robot {
public:    
    vector<int> orders = vector<int>();
    //Initializing the locations to Student Union
    unsigned int currentLocationID = 0;
    vector<int> destinations = vector<int>();
};

class node {
public:    
    string name;
    unsigned int id;
    node(string newName, unsigned int newId){
        this->name = newName;
        this->id = newId;
    }
};

class systemGraph {
public:
    //Initialize all nodes
    node studentUnion = node("Student Union", 0);
    node honorsVillage = node("Honors Village", 1);
    node globalCenter = node("Global Center", 2);
    node scienceEngineeringLibrary = node("Science and Engineering Library", 3);
    node mainLibrary = node("Main Library", 4);
    node gittings = node("Gittings Building", 5);

    //Create an array of these nodes for easy access to name and ID
    node locations[NUM_LOCATIONS] = {studentUnion, honorsVillage, globalCenter, scienceEngineeringLibrary, mainLibrary, gittings};

    //For ease of programming, we will be referring to nodes by their ID
    //Create adjacency list of pairs, with the first entry being the node, and the second being distance 
    // vector<pair<int, int>> adjacencyList[NUM_LOCATIONS];
    
    // //Constructor populating student Union connections
    // systemGraph(){
    //     //Connections for student union
    //     adjacencyList[0].push_back(pair<int, int>(1, 4));
    //     adjacencyList[0].push_back(pair<int, int>(2, 5));
    //     adjacencyList[0].push_back(pair<int, int>(3, 2));
    //     adjacencyList[0].push_back(pair<int, int>(4, 3));
    //     adjacencyList[0].push_back(pair<int, int>(5, 4));
    //     //Connections for Honors Village
    //     adjacencyList[1].push_back(pair<int, int>(0, 4));
    //     adjacencyList[1].push_back(pair<int, int>(2, 6));
    //     adjacencyList[1].push_back(pair<int, int>(4, 6));
    //     adjacencyList[1].push_back(pair<int, int>(5, 5));
    //     //Connections for Global center
    //     adjacencyList[2].push_back(pair<int, int>(0, 5));
    //     adjacencyList[2].push_back(pair<int, int>(1, 6));
    //     adjacencyList[2].push_back(pair<int, int>(3, 4));
    //     //Connections for Science and Engineering Library
    //     adjacencyList[3].push_back(pair<int, int>(0, 2));
    //     adjacencyList[3].push_back(pair<int, int>(2, 4));
    //     adjacencyList[3].push_back(pair<int, int>(4, 1));
    //     //Connections for Main Library
    //     adjacencyList[4].push_back(pair<int, int>(0, 3));
    //     adjacencyList[4].push_back(pair<int, int>(1, 6));
    //     adjacencyList[4].push_back(pair<int, int>(3, 1));
    //     adjacencyList[4].push_back(pair<int, int>(5, 4));
    //     //Connections for Gittings
    //     adjacencyList[5].push_back(pair<int, int>(0, 4));
    //     adjacencyList[5].push_back(pair<int, int>(1, 5));
    //     adjacencyList[5].push_back(pair<int, int>(4, 4));
    // }

    //Halfway through, switched method from adjacency list to adjacency matrix
    int adjacencyMatrix[NUM_LOCATIONS][NUM_LOCATIONS] =
    {
        {0, 4, 5, 2, 3, 4},
        {4, 0, 6, 0, 6, 5},
        {5, 6, 0, 4, 0, 0},
        {2, 0, 4, 0, 1, 0},
        {3, 6, 0, 1, 0, 4},
        {4, 5, 0, 0, 4, 0}
    };

    string getLocationName(int id){
        return locations[id].name;
    }

};
 

 
// Driver code
int main()
{
    //Initialize random
    srand(time(NULL));
    
    //Initialize an array of 5 robots
    robot robots[NUM_ROBOTS];
    
    //Initialize campus graph
    systemGraph campus = systemGraph();

    int numOrders;

    //We enter the program for loop
    while (1){
        //This is the number of orders in the queue
        numOrders = (rand() % 15) + 1;
        vector<int> orderLocations = vector<int>();

        printf("Choose the number of the destination for your orders!\n\n");
        printf("Here are the possible destinations:\n");
        printf("Destination 1: Honors Village\n");
        printf("Destination 2: Global Center\n");
        printf("Destination 3: Science and Engineering Library\n");
        printf("Destination 4: Main Library\n");
        printf("Destination 5: Gittings Building\n\n");
        printf("Type any other number besides 1-5 to exit to exit the program\n\n");

        for(int i = 0; i < numOrders; i++){
            unsigned int choice;
            printf("Order %d: ", i + 1);
            scanf("%d", &choice);
            if(choice < 1 || choice > 5){
                printf("Exiting...");
                return 0;
            }
            orderLocations.push_back(choice);
        }

        printf("\n%d orders received! Calculating a good robot order distributions...\n", numOrders);

        //We want as many robots to have the same delivery location to minimize energy usage
        //To do this, we will sort the orders by location, then start assigning robots to them
        //sort(orderLocations.begin(), orderLocations.end());

        // cout << "Sorted \n";
        // for (auto x : orderLocations)
        //     cout << x << " ";

        //Create a map of all the locations 
        int locationCounter[NUM_LOCATIONS] = {0, 0, 0, 0, 0, 0,};
        for(int i = 0; i < orderLocations.size(); i++){
            locationCounter[orderLocations[i]]++;
        }

        //Make the map from order location to robots
        //We want as many robots to deliver to only one location
        int robotId = 0;
        bool ordersPending = true;
        while (ordersPending && robotId < NUM_ROBOTS) {
            ordersPending = false;

            //Find any packages we can combine all into 1 robot
            for(int i = 0; i < NUM_LOCATIONS; i++){
                if(locationCounter[i] > 2){
                    //We add it 3 times
                    robots[robotId].orders.push_back(i);
                    robots[robotId].orders.push_back(i);
                    robots[robotId].orders.push_back(i);
                    robotId++;
                    ordersPending = true;
                    locationCounter[i] = locationCounter[i] - 3;
                    i--;
                    continue;
                }
            }

            //Do the rest
            for(int i = 0; i < NUM_LOCATIONS; i++){
                while(locationCounter[i] > 0 && robots[robotId].orders.size() < 3){
                    robots[robotId].orders.push_back(i);
                    locationCounter[i]--;
                    ordersPending = true;
                }

                if(robots[robotId].orders.size() > 2){
                    robotId++;
                    i--;
                }
            }
        }
        
        
        // int robotId = 0;
        // for(int i = 0; i < numOrders; i++){
        //     robots[i / 3].orders.push_back(orderLocations[i]);
        // }

        int orderCount = 1;
        for(int i = 0; i < NUM_ROBOTS; i++){
            printf("Robot %d orders:\n", i + 1);
            int robotOrderNum = robots[i].orders.size();
            for(int j = 0; j < robotOrderNum; j++){
                std::cout << "\t" << j + 1 << ": " << campus.getLocationName(robots[i].orders[j]) << std::endl;
                //printf("\t%d: %s\n", j + 1, j + 1, campus.getLocationName(robots[i].orders[j]));
            }

        }
        
         //Populate the routing tables
        int routingTable[NUM_LOCATIONS][NUM_LOCATIONS];
        for(int i = 0; i < NUM_LOCATIONS; i++){
            dijkstra(campus.adjacencyMatrix, i, routingTable);
        }

        //Go through each robot, and determine the best path
        for(int i = 0; i < NUM_ROBOTS; i++){
            int numDestinations = robots[i].orders.size();
            int currentLocation = robots[i].currentLocationID;

            //If there are 3 possible destinations
            if(numDestinations == 3){
                int dest1 = robots[i].orders[0];
                int dest2 = robots[i].orders[1];
                int dest3 = robots[i].orders[2];
                //int dest4 = 0; //Student Union is always the last stop
                
                int sum123 = routingTable[robots[i].currentLocationID][dest1]
                                + routingTable[dest1][dest2]
                                + routingTable[dest2][dest3]
                                + routingTable[dest3][0];
                int sum132 = routingTable[robots[i].currentLocationID][dest1]
                                + routingTable[dest1][dest3]
                                + routingTable[dest3][dest2]
                                + routingTable[dest2][0];
                int sum213 = routingTable[robots[i].currentLocationID][dest2]
                                + routingTable[dest2][dest1]
                                + routingTable[dest1][dest3]
                                + routingTable[dest3][0];
                int sum231 = routingTable[robots[i].currentLocationID][dest2]
                                + routingTable[dest2][dest3]
                                + routingTable[dest3][dest1]
                                + routingTable[dest1][0];
                int sum312 = routingTable[robots[i].currentLocationID][dest3]
                                + routingTable[dest3][dest1]
                                + routingTable[dest1][dest2]
                                + routingTable[dest2][0];
                int sum321 = routingTable[robots[i].currentLocationID][dest3]
                                + routingTable[dest3][dest2]
                                + routingTable[dest2][dest1]
                                + routingTable[dest1][0];

                
                //Find the minimum distance
                int min1 = min(sum123, sum132);
                int min2 = min(sum213, sum231);
                int min3 = min(sum312, sum321);
                int min4 = min(min1, min2);
                int finalMin = min(min4, min3);

                if(finalMin == sum123){
                    robots[i].destinations.push_back(dest1);
                    robots[i].destinations.push_back(dest2);
                    robots[i].destinations.push_back(dest3);
                }

                else if(finalMin == sum132){
                    robots[i].destinations.push_back(dest1);
                    robots[i].destinations.push_back(dest3);
                    robots[i].destinations.push_back(dest2);
                }

                else if(finalMin == sum213){
                    robots[i].destinations.push_back(dest2);
                    robots[i].destinations.push_back(dest1);
                    robots[i].destinations.push_back(dest3);
                }

                else if(finalMin == sum231){
                    robots[i].destinations.push_back(dest2);
                    robots[i].destinations.push_back(dest3);
                    robots[i].destinations.push_back(dest1);
                }

                else if(finalMin == sum312){
                    robots[i].destinations.push_back(dest3);
                    robots[i].destinations.push_back(dest1);
                    robots[i].destinations.push_back(dest2);
                }

                else if(finalMin == sum321){
                    robots[i].destinations.push_back(dest3);
                    robots[i].destinations.push_back(dest2);
                    robots[i].destinations.push_back(dest1);
                }

                else {
                    printf("A huge error has occured.\nExiting...");
                    return -1;
                }

                //All of them need to return to base
                robots[i].destinations.push_back(0);
            }

            //If there are two destinations
            else if(numDestinations == 2){
                int dest1 = robots[i].orders[0];
                int dest2 = robots[i].orders[1];

                int sum12 = routingTable[robots[i].currentLocationID][dest1]
                                + routingTable[dest1][dest2]
                                + routingTable[dest2][0];
                int sum21 = routingTable[robots[i].currentLocationID][dest2]
                                + routingTable[dest2][dest1]
                                + routingTable[dest1][0];


                //Find the minimum distance
                int min1 = min(sum12, sum21);

                if(min1 == sum12){
                    robots[i].destinations.push_back(dest1);
                    robots[i].destinations.push_back(dest2);
                }

                else if (min1 == sum21) {
                    robots[i].destinations.push_back(dest2);
                    robots[i].destinations.push_back(dest1);
                }

                else {
                    printf("A huge error has occured.\nExiting...");
                    return -1;
                }

                //All of them need to return to base
                robots[i].destinations.push_back(0);
                
            }

            else if(numDestinations == 1){
                robots[i].destinations.push_back(robots[i].orders[0]);
                robots[i].destinations.push_back(0);
            }

        }

        //Now that routing has been configured, need to watch execution

        bool finished = false;
        while(!finished){
            finished = true;
            for(int i = 0; i < NUM_ROBOTS; i++){
                if(robots[i].destinations.size() > 0){
                    finished = false;
                    int destinationTemp = robots[i].destinations[0];
                    std::cout << "Robot " << i + 1 << " has reached " << campus.getLocationName(destinationTemp) << std::endl;
                    //Delete the first element, the one that was just reached
                    robots[i].destinations.erase(robots[i].destinations.begin());
                    //Keep deleting if we are in the same location
                    while(robots[i].destinations.size() > 0 && destinationTemp == robots[i].destinations[0]){
                        robots[i].destinations.erase(robots[i].destinations.begin());
                    }
                }
            }
        }

        //Destroy any leftover elements
        for(int i = 0; i < NUM_ROBOTS; i++){
            robots[i].orders.clear();
            robots[i].destinations.clear();
        }
        
    }    


    return 0;
}