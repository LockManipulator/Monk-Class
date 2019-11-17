using namespace std;
class ClassFramework {
public:
	uint8_t getClassCount();
	void initialise();

private:
	map<int, string> classTypes;
};