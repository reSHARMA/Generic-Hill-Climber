#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long int ll;

const ll MOD=1e9+7,INF=0x3F3F3F3F3F3F3F3F;
const int inf=0x3F3F3F3F;
/* Parameters 
 * initial population ip
 * maximum value MAX
 * reproduction factor rp
 * fit threshold height fsh
 * fir threshold diversity fsd
 * mutation rate mt
 * retain factor rt
 * target 
 */
const int ip = 10;
const int MAX = 10000;
const int rp = 2;
const double fsh = .6;
const double fsd = .5;
const double mt = .2;
const double rt = .2;
const int target = 15000;
int A,B,C,D,a,b,c;

int progress = 0;
/*
 * population {x,y}
 */
vector <pair <int,int> > population;
/*
 * meta {{height,diversity},index}
 * meta_height {height,index}
 * meta_diversity {diversity,index}
 */

//vector <pair<pair<int,int>,int > > meta;
vector <pair <int,int> > meta_height;
vector <pair <int,int> > meta_diversity;
/*
 * offsprings {x,y}
 */
vector <pair <int,int> > offsprings;

pair<int,int> init_individual(int min,int max){
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(min,max);
	/*
	int x = min + (rand()%(max+min+1));
	int y = min + (rand()%(max+min+1));
	*/
	int x = dis(gen);
	int y = dis(gen);
	return {x,y};
}

void print_population(){
	cout<<"[";
	int i = 0;
	int last = population.size();
	for(auto p:population){
		cout<<"["<<p.first<<","<<p.second<<"]";
		i++;
		if(i != last){
			cout<<",";
		}
	}
	cout<<"]";
}

int mean_height(){
	//cout<<"					finding mean height"<<endl;
	int sum = 0;
	int i=0;
	for(auto p:population){
		//cout<<"						working on individual "<<i+1<<endl;
		int x = p.first;
		int y = p.second;
		int z = (D - (B*pow(y,b)+A*pow(x,a)))/C; //z^c 
		z = pow(z,1/c); // z
		//meta.push_back({{z,0},i});
		meta_height.push_back({z,i});
		i++;
		sum += z;
	}
	//cout<<"								sum "<<sum<<endl;
	return sum/i;
}

void find_diversity(){
	//cout<<"				finding diversity"<<endl;
	int av_height = mean_height();
	//cout<<"					mean height calculated "<<av_height<<endl;
	//cout<<"					meta_height size "<<meta_height.size()<<endl;
	for(auto m:meta_height){
		//m.first.second = abs(av_height - m.first.first);
		meta_diversity.push_back({abs(av_height - m.first),m.second});
	}
	//cout<<"					meta_diversity size "<<meta_diversity.size()<<endl;
}

int find_best(){
	//cout<<"			finding best"<<endl;
	find_diversity();
	sort(meta_height.rbegin(),meta_height.rend());
	int fs = ceil((double)meta_height.size()*fsh);
	//cout<<"				fs "<<fs<<endl;
	/*
	 * to-do
	 * avoid the below swap
	 * #optimization
	 */
	for(int i=0;i<fs;i++){
		pair <int,int> temp;
		temp = meta_diversity[i];
		meta_diversity[i] = meta_diversity[meta_height[i].second];
		meta_diversity[meta_height[i].second] = temp;
	}
	sort(meta_diversity.begin(),meta_diversity.begin()+fs);
	//fs = fs * fsd;
	//cout<<"				fs "<<fs<<endl;
	return fs;
}

void cross_over(){
	//cout<<"		Cross-over"<<endl;
	for(int i=0;i<meta_height.size()*rt;i++){
		offsprings.push_back(meta_height[i]);
	}
	int fs = find_best();
	for(int i=fs-1;i>=0;i-=2){
		offsprings.push_back({population[i].first,population[i+1].second});
		offsprings.push_back({population[i].second,population[i+1].first});
	}
	fs = fs * fsd;
	for(int i=0;i<fs*(rp-1);i++){
		int father = -1;
		int mother = -1;
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> dis(0,fs);
		while(father == mother){
			father = dis(gen);
			mother = dis(gen);
		}
	offsprings.push_back({population[father].first,population[mother].second});
	}
}

void mutate(){
	//cout<<"		Mutation begins"<<endl;
	int size = offsprings.size();
	//cout<<"		size of offsprings"<<offsprings.size()<<endl;
	for(int i=0;i<size*mt;i++){
		int individual = rand()%size;
		int chance = rand()%2;
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_int_distribution<> dis(-10000,MAX);

		if(chance == 0)
			offsprings[individual].first = dis(gen);
		else 
			offsprings[individual].second = dis(gen);
	}
}

int evolve(){
	cross_over();
	mutate();
	print_population();
	population.clear();
	population = offsprings;
	offsprings.clear();
	meta_height.clear();
	meta_diversity.clear();
	return population.size();
}

int main(){
	fast;
	//cout<<"enter the equation for the mesh"<<endl;
	//Ax^a+By^b+Cz^c=D
	cin>>A>>B>>C>>D>>a>>b>>c;
	for(int i=0;i<ip;i++){
		population.push_back(init_individual(-10000,MAX));
	}
	cout<<"[";
	for(;;){
		int temp = evolve();
		//cout<<"temp "<<temp<<"  progress  "<<progress<<endl;
		progress += temp;
		if(progress > target){
			cout<<"]";
			break;
		} else {
			cout<<",";
		}
	}
	return 0;
}
