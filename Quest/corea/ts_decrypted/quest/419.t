CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 419;
	title = 41902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 41907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4261106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
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
				conv = 41909;
				ctype = 1;
				idx = 4261106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 41908;
				gtype = 2;
				area = 41901;
				goal = 41904;
				m0fz = "-3473.000000";
				m0widx = 1;
				sort = 41905;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "6316.000000";
				m0ttip = 41915;
				rwd = 100;
				taid = 1;
				title = 41902;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7211101;
				cnt0 = 6;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 41908;
			gtype = 2;
			oklnk = 2;
			area = 41901;
			goal = 41904;
			sort = 41905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 41902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 41914;
			nextlnk = 101;
			rwdtbl = 41901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4261106;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

