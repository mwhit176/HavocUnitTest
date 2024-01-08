package plugin

import "errors"

func (s *PluginSystem) AgentGenerate(ctx map[string]any, config map[string]any) ([]byte, error) {
	var (
		err error
		ext *Plugin
		bin []byte
	)

	err = errors.New("agent not found")

	s.loaded.Range(func(key, value any) bool {
		ext = value.(*Plugin)

		if ext.Type != PluginTypeAgent {
			return true
		}

		if ctx["name"] == ext.AgentRegister()["name"] {
			bin, err = ext.AgentGenerate(ctx, config)
			return false
		}

		return true
	})

	return bin, err
}
