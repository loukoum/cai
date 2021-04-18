#pragma once

class AI;
struct AISaveData;

#include "ai/neural-network.h"
#include "game/board.h"

#include <vector>
#include <fstream>

const std::vector<int> PROPAGATOR_LAYOUT = { 64, 100, 80, 64 };
const std::vector<int> ANALYZER_LAYOUT = { 64, 100, 80, 30, 10, 1 };
const std::vector<int> FAST_LOOKUP_LAYOUT = { 64, 30, 10, 1 };
const std::vector<int> CYCLES_MANAGER_LAYOUT = { 2, 4, 3, 1 };
const std::vector<int> NORMALIZER_LAYOUT = { 1, 3, 1 };

struct AISaveData {
	NNSaveData propagator;
	NNSaveData analyzer;
	NNSaveData fastLookup;
	NNSaveData cyclesManager;
	NNSaveData normalizer;
	float fitness;

	AISaveData() { }
	AISaveData(const AISaveData& other) : propagator(other.propagator),
		analyzer(other.analyzer), fastLookup(other.fastLookup),
		cyclesManager(other.cyclesManager), normalizer(other.normalizer),
		fitness(other.fitness) { }
	AISaveData(AISaveData&& other) : propagator(std::move(other.propagator)),
		analyzer(std::move(other.analyzer)),
		fastLookup(std::move(other.fastLookup)),
		cyclesManager(std::move(other.cyclesManager)),
		normalizer(std::move(other.normalizer)),
		fitness(std::move(other.fitness)) { }
	AISaveData(const char* location) {
		loadFromDisk(location);
	}
	AISaveData(std::ifstream& in) {
		loadFromStream(in);
	}

	void saveToDisk(const char* location) const;
	void loadFromDisk(const char* location);
	std::string asString() const;
	void loadFromStream(std::ifstream& inputFile);
};

class AI {
private:
	NeuralNetwork m_propagator;
	NeuralNetwork m_analyzer;
	NeuralNetwork m_fastLookup;
	NeuralNetwork m_cyclesManager;
	NeuralNetwork m_normalizer;
	float m_fitness;

public:
	AI();
	AI(const AI& other) = delete;
	AI(AI&& other) noexcept;
	AI(const AISaveData& saveData);
	AI(const char* location);
	AI(const AI& ai0, const AI& ai1, float mutationProb);

	void save(const char* location) const;
	AISaveData toSaveData() const;
	float cycles(float current, float move);
	float analyze(const std::vector<float>& position, int cycles);
	float fastLookup(const std::vector<float>& position);
	std::vector<float> propagate(const std::vector<float>& inputPosition, int cycles);
	bool operator==(const AI& other) const;
	AI& operator=(AI&& other) { return *this; }

	inline void updateFitness(float delta) { m_fitness += delta; }
	inline float getFitness() const { return m_fitness; }
};

