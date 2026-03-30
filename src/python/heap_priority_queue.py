import heapq
from dataclasses import dataclass, field


@dataclass(order=True)
class Patient:
	priority: int
	arrival_order: int
	name: str = field(compare=False)
	complaint: str = field(compare=False)


class EmergencyQueue:
	def __init__(self):
		self.heap = []
		self.counter = 0

	def push_patient(self, name: str, severity: int, complaint: str):
		item = Patient(priority=-severity, arrival_order=self.counter, name=name, complaint=complaint)
		heapq.heappush(self.heap, item)
		self.counter += 1

	def push(self, name: str, severity: int, complaint: str):
		self.push_patient(name, severity, complaint)

	def pop_next(self):
		if not self.heap:
			return None
		p = heapq.heappop(self.heap)
		return {
			"name": p.name,
			"severity": -p.priority,
			"complaint": p.complaint,
			"arrival_order": p.arrival_order,
		}

	def pop(self):
		return self.pop_next()

	def peek(self):
		if not self.heap:
			return None
		p = self.heap[0]
		return {
			"name": p.name,
			"severity": -p.priority,
			"complaint": p.complaint,
			"arrival_order": p.arrival_order,
		}

	def __len__(self):
		return len(self.heap)


def _format_patient(patient_info):
	if patient_info is None:
		return "None"
	return (
		f"{patient_info['name']} (severity={patient_info['severity']}, "
		f"complaint={patient_info['complaint']}, arrival={patient_info['arrival_order']})"
	)


def run_emergency_simulation():
	eq = EmergencyQueue()

	# 24 olay: arrival, peek ve treat adimlari karisik bir akista tasarlandi.
	events = [
		("arrive", "Ali", 6, "Head Trauma"),
		("arrive", "Zeynep", 9, "Chest Pain"),
		("peek",),
		("arrive", "Mert", 4, "Fever"),
		("treat",),
		("arrive", "Elif", 8, "Severe Burn"),
		("arrive", "Can", 5, "Broken Arm"),
		("peek",),
		("treat",),
		("arrive", "Deniz", 10, "Cardiac Arrest"),
		("arrive", "Ayse", 3, "Migraine"),
		("treat",),
		("peek",),
		("arrive", "Bora", 7, "High Fever"),
		("arrive", "Ece", 8, "Breathing Problem"),
		("treat",),
		("arrive", "Kerem", 2, "Sprain"),
		("arrive", "Ipek", 6, "Deep Cut"),
		("peek",),
		("treat",),
		("treat",),
		("arrive", "Seda", 9, "Stroke Signs"),
		("peek",),
		("treat",),
	]

	print("=== Emergency Service Priority Queue Simulation ===")
	print("Rule: Higher severity is treated first. Tie-breaker: earlier arrival.\n")

	for step, event in enumerate(events, start=1):
		event_type = event[0]
		print(f"[Event {step:02d}] type={event_type}")

		if event_type == "arrive":
			_, name, severity, complaint = event
			eq.push(name=name, severity=severity, complaint=complaint)
			print(f"  - New patient: {name}, severity={severity}, complaint={complaint}")
			print(f"  - Queue size after arrival: {len(eq)}")
			print(f"  - Next to treat: {_format_patient(eq.peek())}")

		elif event_type == "peek":
			next_patient = eq.peek()
			print(f"  - Peek result: {_format_patient(next_patient)}")

		elif event_type == "treat":
			treated = eq.pop()
			print(f"  - Treated patient: {_format_patient(treated)}")
			print(f"  - Queue size after treatment: {len(eq)}")
			print(f"  - Next to treat: {_format_patient(eq.peek())}")

		else:
			print("  - Unknown event, skipped")

		print()

	print("=== Simulation End ===")
	print(f"Remaining patients in queue: {len(eq)}")


if __name__ == "__main__":
	run_emergency_simulation()