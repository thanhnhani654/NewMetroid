#pragma once
#include "Creature.h"
#include "Samus.h"
#include <iostream>

enum eReoState
{
	Idle,				// Tìm đối tượng tấn công
	TiepCan,			// Tiếp cận đối tượng đến một khoảng cách nhất định với tốc độ nhanh
	TruySat,			// Nếu vị trí cao hơn chiều cao của đối tượng thì sẽ hạ độ cao từ từ, còn không thì sẽ giữ nguyên độ cao đó, tốc độ đi theo 
						// đối tượng sẽ không đổi.
	QuayVe,				// Bay trở về tìm chỗ đậu
};

// Cơ chế hoạt động của AI:
// -Ban đầu khi ở trạng thái Idle, khi Samus đi vào tầm phát hiện của nó, nó sẽ chuyển sang trạng thái tiếp cận
// -Ở trạng thái tiếp cận nó sẽ di chuyển theo hình parapoll mà cận chính là tọa độ của người chơi, ở đây có 2 trường hợp:
//	+Tiếp cận không hoàn toàn: ở trạng thái tiếp cận không hoàn toàn, nếu người chơi chuyển sang mode roll nó sẽ chuyển sang State QuayVe
//	+Tiếp cận hoàn toàn: ở trạng thái tiếp cận hoàn toàn thì nếu Samus chuyển sang mode Roll nó sẽ xác định cận parapoll 
//						ở vị trí người chơi va chạm với land, khi đó dù Samus có đứng lên nó vẫn hướng thẳng tới Samus
// -Trong quá trình của trạng thái tiếp cận, nếu người chơi nhảy lên nó sẽ chuyển sang State quay về, nếu tiếp cận đến 1 khoảng cách nhất định 
//	nó sẽ chuyển sang trạng thái TruySat, Lưu ý là trước khi chuyển sang trạng thái truy sát cần phải hoàn thành trạng thái tiếp cận
// -Trong trạng thái TruySat: Nếu tọa độ Samus thấp hơn tọa độ của nó, nó sẽ dần hạ độ cao. Nếu tọa độ Samus cao hơn tọa độ của nó hoặc nó va chạm 
//	 với land nó sẽ chỉ truy sát mà không hạ độ cao

// Note:
// - Quá trình tiếp cận của Reo là 

class Reo : public Creature
{
private:
	eReoState state;
	bool bDetected;						// Phát hiện Samus
	float _IdleMiniumTime;				// Thời gian ở trạng thái Idle tối thiểu không được chuyển trạng thái khác
	
	
	bool bPerfectChase;					// Phân biệt tiếp cận hoàn toàn và tiếp cận không hoàn toàn
	bool bLanding;						// Chạm tường dưới
	bool bParkOnTop;					// Chạm tường trên
	bool bRollingOrFlying;				// Ghi nhớ State của Samus lúc bắt đầu tiếp cận, nếu là Rolling thì sẽ là tiếp cận hoàn toàn
	bool bFlying;						// Nếu Samus thực hiện nhảy sau khi bắt đầu tiếp cận thì nó sẽ chuyển sang State QuayVe
	D3DXVECTOR2 _ClimaxPoint;			// Cận của Parapoll
	float _KillDistance;				// Khoảng cách để chuyển sang trạng thái truy sát

	bool bSlowDown;						// Có truy sát hạ độ cao hay không
	
	float _Sx;							// Khoảng cách Reo với Samus theo X
	float _Sy;							// Khoảng cách Reo với Samus theo y
	float a;							// Gia tốc của X
	bool test;	

	//Properties
	const float _ChaseSpeedX = 180;				// Gia tốc tiếp cận theo X
	const float _ChaseSpeedY = 100;				// Gia tốc tiếp cận theo Y
	const float _SpeedY = -180;

	float _KillingSpeed;				// Vận tốc truy sát


	Box2D box;

	void FixSomeWrongVelocity();		// Sửa lỗi khi bay ngược lên vector vận tốc X bị đổi chiều
	//Behavior
	void StartChase();					// Bắt đầu tính toán gia tốc và vận tốc cần thiết để tấn công mục tiêu
	void ChangeState();
	void ComeBack();
	void Attack();
	void FindSamus();
	void ResetIdle();
public:

#pragma region Inherit

	//Inherit From Creature
	void Initialize();
	void Update(float deltatime);
	void Draw();
	void OnCollision(GameObject* object, float collideTime, int normalX, int normalY);
	void Destroy();							//Dùng để xóa những con trỏ bên trong

#pragma endregion

};