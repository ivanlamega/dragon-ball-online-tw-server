CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 283;
	title = 28302;

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
				conv = 28309;
				ctype = 1;
				idx = 4511206;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 28308;
				gtype = 1;
				area = 28301;
				goal = 28304;
				grade = 132203;
				rwd = 100;
				sort = 28305;
				stype = 2;
				taid = 1;
				title = 28302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 28307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511206;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
			CDboTSCheckClrQst
			{
				and = "236;255;268;";
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
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 28308;
			gtype = 1;
			oklnk = 2;
			area = 28301;
			goal = 28304;
			sort = 28305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 28302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 28314;
			nextlnk = 254;
			rwdtbl = 28301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751106;
			}
		}
	}
}

