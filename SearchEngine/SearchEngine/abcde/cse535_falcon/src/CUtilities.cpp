#include "../include/CUtilities.h"
#include<algorithm>

using namespace std;
std::string CUtilities::stop_word_str ="aaboutaboveafteragainagainstallamanandanyarearen'tasatbebecausebeenbeforebeingbelowbetweenbothbutbycan'tcannotcouldcouldn'tdiddidn'tdodoesdoesn'tdoingdon'tdownduringeachfewforfromfurtherhadhadn'thashasn'thavehaven'thavinghehe'dhe'llhe'sherherehere'shersherselfhimhimselfhishowhow'sii'di'lli'mi'veifinintoisisn'titit'sitsitselflet'smemoremostmustn'tmymyselfnonornotofoffononceonlyorotheroughtouroursourselvesoutoverownsameshan'tsheshe'dshe'llshe'sshouldshouldn'tsosomesuchthanthatthat'sthetheirtheirsthemthemselvesthentherethere'sthesetheythey'dthey'llthey'rethey'vethisthosethroughtotoounderuntilupverywaswasn'twewe'dwe'llwe'rewe'vewereweren'twhatwhat'swhenwhen'swherewhere'swhichwhilewhowho'swhomwhywhy'swithwon'twouldwouldn'tyouyou'dyou'llyou'reyou'veyouryoursyourselfyourselves";
std::string CUtilities::dir_path;
std::string CUtilities::semwiki_dir_path;
std :: string CUtilities::term_indx_dirx_path;
int CUtilities::online_mode_enabled = 0;
int CUtilities::num_for_onlie_mode = 0;
std::string CUtilities::model;
std::string CUtilities::zone;

CUtilities::CUtilities(void) {}

CUtilities::~CUtilities(void) {}

string CUtilities::_file_path_separator = "/";	// TODO: to be changed for final deployment

/**
 * This function prints command help - should be precated and moved to separate classes
 */
void CUtilities::print_command_help()
{
	// need to check this thoroughly
	if (b_verbose_global) std::cout << endl << "Manual: This toolbox will eventually contain some important topic models for text analysis" << endl;
	if (b_verbose_global) std::cout << "Usage: ./TopicModelToolbox blah blah blah" << endl;
	if (b_verbose_global) std::cout << "Example: ./TopicModelToolbox blah blah blah " << endl;
	if (b_verbose_global) std::cout << "\nType ./TopicModelToolbox [--help | -h | /?] anytime for help in running this program" << endl << endl;
	return;
}

/**
 * check if the directory is valid
 */
bool CUtilities::is_valid_directory(const string& dir_name)
{
	bool is_directory = false;
#ifdef UNIX
	struct stat buf;

	if ( stat( dir_name.c_str(), &buf ) == 0 ) {
		if( buf.st_mode & S_IFDIR ) {
			is_directory = true;
		}
	}
#endif

#ifdef CUSTOMIZED
	string dir = dir_name;
	CymString cym_dir(dir);
	util::DirectoryEntry dir_entry(cym_dir);
	is_directory = dir_entry.isDirectory();
#endif

	return is_directory;

}

/**
 * make a directory out of any number of intermediate non-existent levels
 */
bool CUtilities::make_directory(const string& dir_name) {

	bool status = false;

#ifdef UNIX
	if ( dir_name == "" ) return false;
	vector<string> tokens;
	string full_dir = dir_name;
	tokenize(full_dir, tokens, CUtilities::_file_path_separator);

	size_t num_folders = tokens.size();
	if ( num_folders == 0 ) { if (b_verbose_global) std::cout << "something wrong with this filepath " << full_dir << endl; return false; }
	string incremental_path = CUtilities::_file_path_separator;	// we will assume that we have the full path from the root
	for ( size_t f = 0; f < num_folders; ++f ) {
		if ( tokens[f] == "" ) continue;
		incremental_path += tokens[f] ;
		if ( mkdir(incremental_path.c_str(), S_IRWXU ) == 0 ) {
			if (b_verbose_global) std::cout << endl << "made directory " << incremental_path << "  ... yeah!" << endl;
			status |= true;
		}
		else {
			status &= false;
			//if (b_verbose_global) std::cout << "unable to make directory " << incremental_path << " - directory might exist or path is wrong" << endl;
		}
		incremental_path += CUtilities::_file_path_separator;

	}
#endif

#ifdef CUSTOMIZED
	string dir = dir_name;
	CymString cym_dir(dir);
	int err = util::MakeDirectoryRecursive(cym_dir, 0755);
	if ( err ) status = false;
#endif

	return status;
}

/**
 * This function deletes the trailing '/'s from a directory path
 */
void CUtilities::delete_trailing_forward_slashes(string& path)
{
	size_t pos = path.find_last_of('/');
	if ( pos == (path.length() - 1) ) path.erase(pos);
	return;
}

/**
 * This function removes all spaces in a string
 */
void CUtilities::trim(string& token)
{
	string::iterator itr;
	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), ' '));
	token.erase(itr, token.end());

	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), '\r'));
		token.erase(itr, token.end());

	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), '\n'));
		token.erase(itr, token.end());

	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), '\t'));
		token.erase(itr, token.end());

	return;
}

/**
 * This function removes trailing white-spaces ([ \\t\\r\\n]) from the left and right of a string
 */
void CUtilities::trim_left_right(string& token)
{
	int i = 0, j = token.length()-1;
	//if (b_verbose_global) std::cout << token << endl;
	while( (size_t)i < token.length() ) {
		if ( (token[i] == ' ') || (token[i] == '\t') || (token[i] == '\r') || (token[i] == '\n') )
			i++;
		else break;
	}
	i = ((size_t)i > token.length()-1) ? token.length()-1 : i;
	//if (b_verbose_global) std::cout << " i = " << i << endl;
	while( j >= 0 ) {
		if ( (token[j] == ' ') || (token[j] == '\t') || (token[j] == '\r') || (token[i] == '\n') )
			j--;
		else break;
	}
	j = (j < 0) ? 0 : j+1;
	//if (b_verbose_global) std::cout << " j = " << j << endl;

	token.erase(0, i);			// left erase

	if ( ((size_t)j < token.length()) && (token.length() != 0 ) )
		token.erase(j, string::npos);	// right erase

	//if (b_verbose_global) std::cout << token << endl;

	return;
}

/**
 * This function deletes all dashes in a string
 */
void CUtilities::delete_dashes(string& token)
{
	string::iterator itr;
	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), '-'));
	token.erase(itr, token.end());
	return;
}

/**
 * This functions deletes the character passed in the second parameter from the string passed in the first parameter
 */
void CUtilities::delete_character(string& token, char c) {
	string::iterator itr;
	itr = remove_if(token.begin(), token.end(), bind2nd(equal_to<char>(), c));
	token.erase(itr, token.end());
	return;
}

/**
 * This function deletes non alpha numeric characters to the extreme right and left of a string
 */
void CUtilities::delete_non_alphanum_left_right(string& token)
{
	string toMatch = "qwertasdfgzxcvbyuiophjklnm1QWERTASDFGZXCVBYUIOPHJKLNM234567890";
	size_t posLast = token.find_last_of(toMatch);
	size_t posFirst = token.find_first_of(toMatch);

	if ( posLast != (token.length()-1) )	// need to trim right
		token.erase(posLast+1);
	if ( posFirst != 0 )	// need to left trim
		token.erase(0,posFirst);

	return;
}

/**
 * This function makes a string to its lowercase equivalent
 */
void CUtilities::to_lower(string& token)
{
	std::transform(token.begin(), token.end(), token.begin(), SToLower());
}
void CUtilities::remove_duplicates(std::vector<string>& token_vec) {

std::sort(token_vec.begin(), token_vec.end());

std::vector<std::string>::iterator new_end_pos;
std::vector<std::string>::iterator start_pos(token_vec.begin() );
std::vector<std::string>::iterator end_pos( token_vec.end() );

new_end_pos = std::unique(token_vec.begin(), token_vec.end() );
std::string value( *start_pos );

while (++start_pos != end_pos)
{
end_pos = std::remove( start_pos, end_pos, value );
value = *start_pos;
}

new_end_pos = std::unique( token_vec.begin(), token_vec.end() );
token_vec.erase( new_end_pos, token_vec.end() );
}

/**
 * This function tokenizes a string into tokens based on an array of character delimiters
 * For eficiency reasons, the separated tokens are pushed back into a stl vector of std::strings
 * Care should be taken to clear this vector every time this method is called
 */
void CUtilities::tokenize(string& str, vector<string>& tokens, const string& delimiters)
{
	// Skip delimiters at beginning.
    size_t lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    size_t pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.

    	string temp= str.substr(lastPos, pos - lastPos);
    	if(stop_word_str.find(temp)==string::npos)
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

	return;
}

//

bool CUtilities::compareFirstPredDescending_pairDoubleInt(const pair_double_int& left, const pair_double_int& right)
{
	return left.first > right.first;
}
bool CUtilities::compareFirstPredAscending_pairDoubleInt(const pair_double_int& left, const pair_double_int& right)
{
	return left.first < right.first;
}

bool CUtilities::compareSecondPredDescending_pairStringDouble(const pair_string_double& left, const pair_string_double& right)
{
	return left.second > right.second;
}
bool CUtilities::compareSecondPredAscending_pairStringDouble(const pair_string_double& left, const pair_string_double& right)
{
	return left.second < right.second;
}

/*
 * -------------- Mathematical Functions ----------------
 */


/*
 * returns the max of the lements in the vector<double> v and
 * the index of the max element is kept in the reference index
 * complexity - O(N) where N is the # of elements in the vector
 */
double CUtilities::max_index_vector_double(vector<double> *v, int &index)
{
	double mx = 0.0;
	for (size_t i = 0; i < v->size(); i++) {
		//if (b_verbose_global) std::cout << " " << v->at(i);
		if ( v->at(i) > mx ) {
			mx = v->at(i);
			index = i;
		}
	}
	//if (b_verbose_global) std::cout << endl;
	//if (b_verbose_global) std::cout << index << endl;
	return mx;
}
int CUtilities::toInt(string str){
	return atoi(str.c_str());
}
