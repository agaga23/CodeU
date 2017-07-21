#include <iostream>
#include <string> 
#include <vector>
class Move{
public:
	int from, to;
	std::string to_string(){
		return "move from " + std::to_string(from) + " to " + std::to_string(to);
	}
	Move ( int initially, int finally ):
		from { initially }, to { finally }
	{}
};
class Parking{
	std::vector < int > cars, carsPositions;
	int zeroPosition;
	
	void go ( Move move ){
		carsPositions[cars[move.from]] = move.to;
		carsPositions[cars[move.to]] = move.from;
		
		std::swap ( cars[move.from], cars[move.to] );
	}

public:
	std::vector<Move> transformTo ( const Parking& finalParking ){
		
		std::vector<Move> moves;
		int nextPositionToCheck = 0;
		while ( nextPositionToCheck < cars.size() ){
			if ( zeroPosition != finalParking.zeroPosition ){
				
				int carToMove = finalParking.cars[zeroPosition]; //this car should be on the zeroPosition finally
				int carToMovePosition = carsPositions[carToMove]; //where the car is now
				
				Move putOnFinalPlace(carToMovePosition, zeroPosition);
				
				go ( putOnFinalPlace );
				zeroPosition = carToMovePosition;

				moves.push_back ( putOnFinalPlace );
			}
			else{
				while ( nextPositionToCheck < cars.size() && cars[nextPositionToCheck] == finalParking.cars[nextPositionToCheck] ) nextPositionToCheck ++;
				
				if ( nextPositionToCheck < cars.size() ){ //the car on nextPositionToCheck position wouldn't be there finally, so move it to make space for another one

					Move makeSpace(nextPositionToCheck, zeroPosition);

					go ( makeSpace );
					zeroPosition = nextPositionToCheck;

					moves.push_back ( makeSpace );
				}
			}
		}
		return moves;
	}
	Parking ( std::vector<int> array ):
		cars{ array }{
			carsPositions.resize ( array.size() );
			for ( int i = 0; i < array.size(); i ++ ){
				int car = array[i];
				carsPositions[car] = i;
			}
			zeroPosition = carsPositions[0];
		}
};
void printing ( std::vector < Move > moves ){
	for ( Move move: moves ){
		std::cout << move.to_string() << "\n";
	}
	std::cout << "----------------------------\n";
}
void generateMoves ( std::vector<int> before, std::vector<int> after ){
	Parking parking( before );
	std::vector<Move> moves = parking.transformTo( Parking(after) );
	printing(moves);
}
int main(){
	std::vector < int > before = {1,2,0,3}, after = {3,1,2,0};
	generateMoves ( before, after );

	generateMoves ( {1,2,0,3}, {2,1,3,0} );
}