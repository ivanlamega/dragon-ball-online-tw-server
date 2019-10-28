CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 550;
	title = 55002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 55031;
				ctype = 1;
				idx = 2611202;
				taid = 1;
			}
		}
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
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 55009;
				ctype = 1;
				idx = 2611101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 55008;
				gtype = 1;
				area = 55001;
				goal = 55004;
				m0fz = "-1424.000000";
				m0widx = 1;
				sort = 55005;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "7000.000000";
				m0ttip = 55015;
				rwd = 100;
				taid = 1;
				title = 55002;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 55014;
			nextlnk = 101;
			rwdtbl = 55001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 55008;
			gtype = 1;
			oklnk = 2;
			area = 55001;
			goal = 55004;
			sort = 55005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 55002;
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
			stdiag = 55007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 2611101;
			}
			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckClrQst
			{
				and = "539;";
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 1;
			yeslnk = 4;

			CDboTSSkillUse
			{
				idx = 520121;
				rp = 0;
				stype = 3;
				tidx = 2611202;
				ttype = 1;
			}
		}
	}
}

