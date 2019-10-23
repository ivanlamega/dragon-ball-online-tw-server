CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 403;
	title = 40302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 40309;
				ctype = 1;
				idx = 4371202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 40308;
				gtype = 0;
				area = 40301;
				goal = 40304;
				grade = 132203;
				rwd = 100;
				sort = 40305;
				stype = 2;
				taid = 1;
				title = 40302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 40307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 9;
				minlvl = 1;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4371202;
			}
			CDboTSCheckClrQst
			{
				and = "402;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 40308;
			gtype = 0;
			oklnk = 2;
			area = 40301;
			goal = 40304;
			sort = 40305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 40302;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 40314;
			nextlnk = 254;
			rwdtbl = 40301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
		}
	}
}

