CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1;
	title = 102;

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
				tidx = 4911100;
				tt = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 108;
				gtype = 1;
				area = 101;
				goal = 104;
				m0fz = "4408.000000";
				m0widx = 1;
				sort = 105;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4601.000000";
				m0ttip = 115;
				rwd = 100;
				taid = 1;
				title = 102;
			}
			CDboTSActNPCConv
			{
				conv = 109;
				ctype = 1;
				idx = 3221202;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 108;
			gtype = 1;
			oklnk = 2;
			area = 101;
			goal = 104;
			sort = 105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 102;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 114;
			nextlnk = 254;
			rwdtbl = 101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3221202;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
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
	}
}

