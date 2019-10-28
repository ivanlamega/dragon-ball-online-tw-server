CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 401;
	title = 40102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSScoutUse
			{
				idx = 17001;
				tidx = 7211100;
				tt = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 40109;
				ctype = 1;
				idx = 4371202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 40108;
				gtype = 1;
				area = 40101;
				goal = 40104;
				m0fz = "-4161.000000";
				m0widx = 1;
				sort = 40105;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "6318.000000";
				m0ttip = 40115;
				rwd = 100;
				taid = 1;
				title = 40102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 40107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4371202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 9;
				minlvl = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 40108;
			gtype = 1;
			oklnk = 2;
			area = 40101;
			goal = 40104;
			sort = 40105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 40102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 40114;
			nextlnk = 254;
			rwdtbl = 40101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371202;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

