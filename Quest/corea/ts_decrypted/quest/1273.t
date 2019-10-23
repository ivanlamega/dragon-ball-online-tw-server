CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1273;
	title = 127302;

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
				conv = 127309;
				ctype = 1;
				idx = 4372101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 127308;
				gtype = 1;
				area = 127301;
				goal = 127304;
				grade = 132203;
				rwd = 100;
				sort = 127305;
				stype = 1;
				taid = 1;
				title = 127302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 127307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
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
			cont = 127308;
			gtype = 1;
			oklnk = 2;
			area = 127301;
			goal = 127304;
			sort = 127305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 127302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 127314;
			nextlnk = 254;
			rwdtbl = 127301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7611203;
			}
		}
	}
}

