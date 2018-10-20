/* SHILADITYA BISWAS - Orienteering Tsiligirides - IIT MADRAS (Computer Science & Engineering) */


#include<bits/stdc++.h>
using namespace std;

#define alpha .50
#define beta  .20
#define gamma .30
#define iteration_limit 10

struct node {
	int node_no;
	float x;
	float y;
	float time;
	int  score_rank;
	int cog_rank;
	int  elps_rank;
	double weigh_rank;
	double distance; // Sum total of distance from two foci of an ellipse
	double distance_to_cog; // Distance to the cog of the entire network
	double a;
	double ratio_sa;

};

void print_vector(vector <node*> points){
	
	cout << " NODE NUMBER " << " X-CORD " << " Y-CORD " << " SCORE/TIME " << " SCORE_RANK " << endl;
	for(int i=0;i<points.size();i++)
		cout << points[i]->node_no << " --> " << points[i]->x << "   " << points[i]->y << "   " << points[i]->time << "   " << points[i]->score_rank << endl; 
}

bool compare_score(const struct node* a, const struct node* b){

	if(a->time > b->time)
		return true;
	else
		return false;
}

bool compare_ellipse_rank(const struct node* a, const struct node* b){

	if(a->distance < b->distance)
		return true;
	else
		return false;
}

bool compare_cog_rank(const struct node* a, const struct node* b){

	if(a->distance_to_cog < b->distance_to_cog)
		return true;
	else
		return false;
}

bool compare_weigh_rank(const struct node* a, const struct node* b){

	if(a->weigh_rank < b->weigh_rank)
		return true;
	else
		return false;
}

bool compare_sa(const struct node* a, const struct node* b){

	if(a->ratio_sa > b->ratio_sa)
		return true;
	else
		return false;
}

double cal_distance(float x,float y,node* f1,node* f2){

	double dist = 0;
	dist += sqrt((x-f1->x)*(x-f1->x) + (y-f1->y)*(y-f1->y));
	dist += sqrt((x-f2->x)*(x-f2->x) + (y-f2->y)*(y-f2->y));

	return dist;
}

void assign_score_ranks(vector <node*> points) {
	int cur_rank = 1;

	for(int i=1;i<points.size();i++){
		if(points[i-1]->time > points[i]->time){
			points[i-1]->score_rank = cur_rank++;
			points[i]->score_rank = cur_rank;
		}
		else{
			points[i-1]->score_rank = cur_rank;
			points[i]->score_rank = cur_rank;
		}

	}
}

void assign_ellipse_rank(vector <node*> points,node* f1,node* f2){

	for(int i=0;i<points.size();i++){
		points[i]->distance = cal_distance(points[i]->x,points[i]->y,f1,f2);
	}

	sort(points.begin(),points.end(),compare_ellipse_rank);
	
	int ellipse_rank =1;

	for(int i=0;i<points.size();i++)
		points[i]->elps_rank = ellipse_rank++;

} 

float cal_cog(float x,float y){
	return (x+y)/2;
}

void assign_cog_rank(vector <node*> points,float cog_x,float cog_y){

	for(int i=0;i<points.size();i++){
		points[i]->distance_to_cog = sqrt((points[i]->x-cog_x)*(points[i]->x-cog_x) + (points[i]->y-cog_y)*(points[i]->y-cog_y));
	}

	sort(points.begin(),points.end(),compare_cog_rank);

	int cog_rank =1;

	for(int i=0;i<points.size();i++)
		points[i]->cog_rank = cog_rank++;

	// print_vector(points);
}

vector <node*> process_nodes(vector <node*> points){

	for(int i=0;i<points.size();i++){
		points[i]->weigh_rank = (alpha*points[i]->score_rank) + (beta*points[i]->cog_rank) + (gamma*points[i]->elps_rank);
	}
	// print_vector(points);
	sort(points.begin(),points.end(),compare_weigh_rank);
	// cout << " -------------------------------\n";
	// print_vector(points);

	return points;
}

vector <node*> final_route_construct(vector <node*> points,int tmax,node* start,node* end){

	float max_val = 0;
	vector <node*> result;
	result.push_back(start);

	// cout << start << " -- " << end << endl;

	for(int i=0;i<points.size();i++){
		if(points[i]->node_no != start->node_no && points[i]->node_no != end->node_no){
			if(max_val + points[i]->time > tmax)
				break;
			else{
				max_val = max_val + points[i]->time;
				result.push_back(points[i]);
			}
	   }
	}

	result.push_back(end);
	return result;

}

double calculate(vector <node*> points){
	
	double cur_distance = 0;
	
	for(int i=0;i<points.size()-1;i++){
    	cur_distance += sqrt(((points[i+1]->x - points[i]->x)*(points[i+1]->x - points[i]->x)) + ((points[i+1]->y - points[i]->y)*(points[i+1]->y - points[i]->y))); 
    	// cout << cur_distance << endl;
    }

    return cur_distance;
}

vector <node*> two_opt(vector <node*> points,double best_distance){

vector <node*> result = points;
bool flag = true;

while(flag){

	int count = 0;

	for(int i=1;i<points.size()-1;i++)
		for(int k=i+1;k<points.size()-1;k++){
			swap(points[i],points[k]);
			double cur_dist = calculate(points);
			// cout << cur_dist << endl;
			
			if(cur_dist < best_distance){
				count++;
				best_distance = cur_dist;  //Updating best distance and storing the best route
				result.clear();
				// cout << "Entered\n";
				for(int i=0;i<points.size();i++)
					result.push_back(points[i]);
			}
		}
		if(count == 0)
			flag = false;
	}

	return result;
}


int main(){

   vector <node*> points;

   float tmax, path;
   cin >> tmax >> path;
   getchar(); 

   string str;
   float a,b,c;
   int count =0;

   float cog_x = 0; // Centre of gravity x-coordinate
   float cog_y = 0; // Centre of gravity y-coordinate

   while (getline(cin, str)) {
		if (!str.empty()){
			istringstream is(str);
			is >> a >> b >> c;

			// Calculating Centre of Gravity after each insertion
			cog_x = cal_cog(a,cog_x);
			cog_y = cal_cog(b,cog_y);
			
			node* temp = new node;
			temp->node_no = count;
			temp->x = a;
			temp->y = b;
			temp->time = c;
			points.push_back(temp);
			count++;
		}
	}

	// print_vector(points);

	// cout << cog_x << " -- " << cog_y << endl;


	node* foci_1 = points[0]; //Starting Point
	node* foci_2 = points[points.size()-1]; //Termination Point

	// cout << foci_1->node_no << endl;
	// cout << foci_2->node_no << endl;
 
	// print_vector(points);

	//Implementation of New Centre of gravity Heuristic
	//http://www.inf.unibz.it/dis/teaching/SDB1314/papers/batch2a.pdf

	/*First STEP : Route Construction
	In this step the objective is to find a route that begins at 1 
	and ends at n which has a relatively high score while requiring less than TMAX units of time 
	*/

	/* The score rank assigns a one to the node with the largest score and increasing ranks,
	 as the scores decrease. Any tie scores are assigned equivalent ranks. */

	cout << "\n\n------------STEP 1: Starting Route Construction---------------\n\n";

	cout << " Value of alpha: " << alpha << " Value of beta: " << beta << " Value of gamma: " << gamma << endl; 

	sort(points.begin(),points.end(),compare_score); // Score wise sorting

	cout << "\n\n------------ 1.1  Finding Score Ranks ---------------\n\n";
	assign_score_ranks(points);
	

	/*The ellipse rank uses the start and end nodes as foci of an ellipse.
	A rank of one is given to the node with the smallest sum of distances to the two foci.
	Increasing ranks are assigned to nodes in ascendingorder of distance. 
	*/
	cout << "\n\n------------ 1.2  Finding Ellipse Ranks ---------------\n\n";
	assign_ellipse_rank(points,foci_1,foci_2);

	cout << "\n\n------------ 1.3  Finding Centre of Gravity Ranks ---------------\n\n";
	assign_cog_rank(points,cog_x,cog_y);
	   

    points = process_nodes(points); //Returning the vector points with ordering as per weighted rank
	
	/* Clearly, at each step we choose the node with the smallest WR(1) as the node to be inserted onto the route.
	 We then apply a cheapest insertion procedure. We continue to insert nodes as long as Th4,AX is not violated.
	 At termination, the route is passed to the route improvement step. */

    vector <node*> rc_result;

    rc_result = final_route_construct(points,tmax,foci_1,foci_2);

    // cout << "TMAX is: " << tmax << endl;


    cout << "The final route after Step1 : Route Construction Heuristic is" << endl;

    for(int i=0;i<rc_result.size();i++)
    	cout << rc_result[i]->node_no << " " ;
    
    cout << endl;



    cout << "\n\n------------STEP 2: Starting Route Improvement ---------------\n\n";
    	
    // print_vector(rc_result);

    double cur_distance = 0;

    // for(int i=0;i<rc_result.size()-1;i++){
    // 	cur_distance += sqrt(((rc_result[i+1]->x - rc_result[i]->x)*(rc_result[i+1]->x - rc_result[i]->x)) + ((rc_result[i+1]->y - rc_result[i]->y)*(rc_result[i+1]->y - rc_result[i]->y))); 
    // 	// cout << cur_distance << endl;
    // }

    cur_distance = calculate(rc_result);

    double best_distance = cur_distance;
    // cout << best_distance << endl;

    vector <node*> two_opt_result = two_opt(rc_result,best_distance);

    cout << "The final route after Step1 : Route Improvement Heuristic is" << endl;

    for(int i=0;i<two_opt_result.size();i++)
    	cout << two_opt_result[i]->node_no << " ";

    cout << endl;

    cout << "\n\n------------STEP 3: Centre of Gravity ---------------\n\n";

    int loop_count = 0;

    vector <node*> routes;
    best_distance = INT_MAX;

    while(loop_count != iteration_limit){

		    double x,y;

		    double sum_total =0;
		    double sum =0;

		    for(int i=0;i<two_opt_result.size();i++){
		    	sum_total = sum_total + two_opt_result[i]->time*two_opt_result[i]->x;
		    	sum = sum + two_opt_result[i]->time;
		    }

		    x = sum_total/sum;

		    sum_total = 0;

		    for(int i=0;i<two_opt_result.size();i++){
		    	sum_total = sum_total + two_opt_result[i]->time*two_opt_result[i]->y;
		    }

		    y = sum_total/sum;

		    cout << "Centre of gravity: " << x << " , " << y << endl;

		    for(int i=0;i<points.size();i++){
		    	points[i]->a = sqrt((x-points[i]->x)*(x-points[i]->x) + (y-points[i]->y)*(y-points[i]->y));
		    }

		    for(int i=0;i<points.size();i++){
		    	points[i]->ratio_sa = (points[i]->time)/(points[i]->a);
		    }

		    //Add routes untill it violates budget TMAX

		    sort(points.begin(),points.end(),compare_sa);

		    two_opt_result.clear();
		    two_opt_result.push_back(foci_1); // Adding start point

		    int max_count_tmax = 0;

		    // for(int i=0;i<points.size();i++)
		    // 	cout << points[i]->node_no << endl;

		    for(int i=0;i<points.size();i++){
		    	if(points[i]->node_no != foci_1->node_no & points[i]->node_no != foci_2->node_no){
		    		if(points[i]->time + max_count_tmax <= tmax){
		    			max_count_tmax += points[i]->time;
		    			two_opt_result.push_back(points[i]);
		    			// cout << max_count_tmax <<  " " << points[i]->time << " " << points[i]->node_no << endl;
		    		}
		    		else
		    			break;
		    	}
		    	else
		    		;
		    }

		    two_opt_result.push_back(foci_2); // Adding end point

		    // cur_distance = calculate(two_opt_result);

		    // best_distance = cur_distance;
		    // cout << best_distance << endl;

		    two_opt_result = two_opt(two_opt_result,best_distance);

		    for(int i=0;i<two_opt_result.size();i++)
		    	cout << two_opt_result[i]->node_no <<  " ";

		    cout  << "Distance: " ;

		    double new_dist = calculate(two_opt_result);
		    
		    cout << new_dist << endl;

		    if(new_dist < best_distance){
		    	best_distance = new_dist;
		    	routes.clear();
		    	for(int i=0;i<two_opt_result.size();i++)
		    		routes.push_back(two_opt_result[i]);
			}


		    loop_count++;
		}  	
		int sum = 0;
		cout << "\n\nThe Final Route after STEP 3 : Centre of Gravity Step is: \n";
		for(int i=0;i<routes.size();i++){
			cout << routes[i]->node_no << " -->  " << routes[i]->time << endl ;
			sum += routes[i]->time;
		}

		cout << endl;

		cout << "Total Score: " << sum << endl;


		//Writing Output to file
		
		ofstream myfile;
		myfile.open("route_co-ordinates.txt");
		for(int i=0;i<routes.size();i++)
			myfile << routes[i]->x << "   " << routes[i]->y << endl;

		cout << "Writing to file done!!!" << endl;
		myfile.close(); 

		

}